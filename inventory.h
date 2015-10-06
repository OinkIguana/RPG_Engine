#ifndef __RPG_INVENTORY_H__
#define __RPG_INVENTORY_H__

#include "stats.h"
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <fstream>

const unsigned int DEFAULT_MAX_STACK = 99;

enum { BUY, SELL };

class ItemType {
	friend class Inventory;
	friend class Item;
	friend class ItemStack;
public:
    /*
        Find an existing item type by its name, returning the pointer. 
        If the type does not yet exist, it is created with the given values. 

        Name, Desc, Buy, Sell, Max stack, Attributes, Kind, Rarity Stats
    */
	static ItemType* get(   const std::string, const std::string = "", 
                            const int = 0, const int = 0, const unsigned int = DEFAULT_MAX_STACK, 
                            const unsigned int = 0, const unsigned int = 0, const unsigned int = 0,
                            const StatList base_stats = StatList());
    ~ItemType() { all_types.erase(_name); }
    /*
        Import item types from a file similar to an ini file:
        ---------------------------
        CONSTANT_NAME=value
        BINARY_CONSTANT=|value
                    ...
        [_name]
        desc=_desc
        buy=_price[BUY]
        sell=_price[SELL]
        max_stack=_max_stack
        attributes=_attributes
        kind=_kind
        rarity=_rarity
        stats=_base_stats
        [_name]
                    ...
        ---------------------------
        Constants can be set at the top for use in _attributes and _kind
        _base_stats is in StatList format.
        Omitting an option sets it to default
    */
    static void import(const std::string);
private:
	ItemType(   const std::string name, const std::string desc = "", 
                const int buy = 0, const int sell = 0, const unsigned int max_stack = DEFAULT_MAX_STACK, 
                const unsigned int attributes = 0, const unsigned int kind = 0, const unsigned int rarity = 0,
                const StatList base_stats = StatList())
		: _name(name), _desc(desc), _price{ buy, sell }, _max_stack(max_stack), _attributes(attributes), _kind(kind), _rarity(rarity), _base_stats(base_stats) {}

	const std::string _name;
	const std::string _desc;
	const int _price[2];
	const unsigned int _max_stack;
	const unsigned int _attributes;
    const unsigned int _kind;
	const StatList _base_stats;
    const int _rarity;

	static std::map<std::string, ItemType*> all_types;
};

class Item {
public:
	Item(ItemType* type = nullptr, int level = 1, StatList stats = StatList()) : _type(type), _level(level), _stats(stats) {}
	~Item() {}
	
	inline int level() { return _level; }
	inline Item upgrade(StatList c = StatList()) { return _stats += c, *this; }
	inline Item level_up() { return ++_level, *this; }

	inline StatList base_stats() { return _type->_base_stats; }
	inline StatList bonus_stats() { return _stats; }
	inline StatList total_stats() { return _stats + _type->_base_stats; }

	operator bool() const { return _type != nullptr; }
	inline ItemType* type() const { return _type; }
private:
	ItemType* _type;
	int _level;
	StatList _stats;
};

class ItemStack {
public:
	ItemStack(ItemType* type = nullptr) : _type(type), _items(new Item*[type == nullptr ? 1 : type->_max_stack]) {}
	~ItemStack() {
        for (unsigned int i = 0; i < _type->_max_stack; i++) {
            delete _items[i];
        }
        delete[] _items; 
    }

	inline ItemType* type() { return _type; }

    /*
        Merges the contents of two ItemStacks, emptying the second
        Returns the remainder of the second stack, which is possibly empty or the whole stack
    */
	ItemStack operator+=(ItemStack&);
    /*
        Adds an Item to the ItemStack.
        Returns the empty stack on success, or the the Item in a stack if it failed
    */
	ItemStack operator+=(Item*);

	inline Item* first() const { return _items[0]; }
	inline Item* last() const { return _items[_length - 1]; }
    /*
        Returns a substack of an ItemStack
    */
	ItemStack slice(const int, const int) const;
	Item* operator[](const int i) { return i < _length ? _items[i] : nullptr; }

    /*
        Removes the given Item from the stack.
        Returns the Item removed, or nullptr if the item was not found
    */
	Item* remove(Item*);
    /*
        Removes the Item at the given index in the stack.
        Returns the Item removed, or nullptr if the item was not found.
    */
	Item* remove(unsigned int);
    /*
        Removes a substack of the ItemStack.
        Returns the removed substack as a new ItemStack.
    */
	ItemStack splice(const int, const int);

	inline unsigned int length() const { return _length; }
	inline bool full() const { return _length == _type->_max_stack; }

	operator bool() const { return _type != nullptr && _length > 0; }
private:
	ItemType* _type;
	Item* * _items;

	unsigned int _length = 0;

    /*
        Sorts the list in order of decreasing levels, with all nullptrs at the end
    */
	inline void sort() { std::sort(_items, _items + _type->_max_stack,
        [](Item* a, Item* b) {
            return (a == nullptr ? 0 : a->level) > (b == nullptr ? 0 : b->level); 
        });
    }
};

class Inventory {
public:
    Inventory(int slot_count) : _length(slot_count) { _slots = new ItemStack[slot_count], sort.inv = this; }
    ~Inventory() { delete[] _slots; }

	inline unsigned int length() const { return _length; }
    ItemStack operator[](const int i) { return _slots[i]; }
    int count(ItemType*) const;
    int count_individual(ItemType*) const;
    int find(ItemType*, const int = 0) const;
    int r_find(ItemType*, const int = 0) const;

    /*
        Merge all stacks of the same type into one (if possible)
    */
    void merge();
    
    /*
        Provides a number of sorting functions for different orders.
    */
    struct {
        typedef std::function<bool(ItemStack*, ItemStack*)> SortFunction;
        Inventory* inv;
        /*
            Sort function to sort in alphabetical order
        */
        inline void alphabetical() {
            _sort([](ItemStack* a, ItemStack* b) { return a->type()->_name < b->type()->_name; });
        }
        /*
            Sort function to sort in order of quantity. Alphabetical if they are equal
        */
        inline void count() {
            _sort([this](ItemStack* a, ItemStack* b) {
                if (a->type() == b->type()) {
                    return a->length() > b->length();
                } else {
                    int ca = inv->count_individual(a->type()), cb = inv->count_individual(b->type());
                    if (ca == cb) {
                        return a->type()->_name < b->type()->_name;
                    }
                    return ca > cb;
                }
            });
        }
        /*
            Sort function to separate out false ItemStacks
        */
        inline void exist() {
            _sort([](ItemStack* a, ItemStack* b) { return (bool)a == (bool)b ? true : a; });
        }

        /*
            Sort by kind of item, optionally offset to have another ItemKind be first.
        */
        inline void kind(const unsigned int first = 0) {
            _sort([first](ItemStack* a, ItemStack* b) {
                if (a->type()->_kind == b->type()->_kind) {
                    return a->type()->_name < b->type()->_name;
                }
                if (a->type()->_kind < first) {
                    if (b->type()->_kind >= first) {
                        return false;
                    }
                } else if (b->type()->_kind < first) {
                    return true;
                }
                return a->type()->_kind < b->type()->_kind;
            });
        }

        /*
            Sort by custom function
        */
        inline void custom(SortFunction f) { _sort(f); }
    private:
        inline void _sort(SortFunction f) {
            inv->merge();
            std::sort(inv->_slots, inv->_slots + inv->_length, f);
        }
    } sort;
private:
	ItemStack * _slots;
	const unsigned int _length;
};

int main() {
    Inventory x(15);
    x.sort.exist();
}

#endif