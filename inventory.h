#pragma once

#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include "sprite.h"
#include "stats.h"
#include "util.h"

const unsigned int DEFAULT_MAX_STACK = 99;

enum { BUY, SELL };

// A type of item
class ItemType {
public:
    /*
        Find an existing item type by its name, returning the pointer.
        If the type does not yet exist, it is created with the given values.

        Name, Desc, Buy, Sell, Max stack, Attributes, Kind, Rarity Stats
    */
    static ItemType* get(   const std::string name, const std::string desc = "",
                            const int buy = 0, const int sell = 0, const unsigned int stack = DEFAULT_MAX_STACK,
                            const unsigned int attr = 0, const unsigned int kind = 0, const unsigned int rarity = 0,
                            const StatList base_stats = StatList(), Sprite* sprite = nullptr);
    inline ~ItemType() { all_types.erase(_name); }
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
        image=_sprite

        [_name]
                    ...
        ---------------------------
        Constants can be set at the top for use in _attributes and _kind
        _base_stats is in StatList format.
        Omitting an option sets it to default
    */
    static void import(const std::string);
    // Delete all types from the list
    inline static void delete_all() { all_types.clear(); }

    inline std::string name() const         { return _name; }
    inline std::string desc() const         { return _desc; }
    inline int buy() const                  { return _price[BUY]; }
    inline int sell() const                 { return _price[SELL]; }
    inline unsigned int max_stack() const   { return _max_stack; }
    inline unsigned int attributes() const  { return _attributes; }
    inline unsigned int kind() const        { return _kind; }
    inline int rarity() const               { return _rarity; }
    inline StatList base_stats() const      { return _base_stats; }
    inline Sprite* sprite() const           { return _sprite; }
private:
    // Create the new ItemType
    ItemType(   const std::string name, const std::string desc = "",
                const int buy = 0, const int sell = 0, const unsigned int max_stack = DEFAULT_MAX_STACK,
                const unsigned int attributes = 0, const unsigned int kind = 0, const unsigned int rarity = 0,
                const StatList base_stats = StatList(), Sprite* sprite = nullptr)
        : _name(name), _desc(desc), _price{ buy, sell }, _max_stack(max_stack), _attributes(attributes), _kind(kind), _rarity(rarity), _base_stats(base_stats), _sprite(sprite) {}

    const std::string   _name;
    const std::string   _desc;
    const int           _price[2];
    const unsigned int  _max_stack;
    const unsigned int  _attributes;
    const unsigned int  _kind;
    const StatList      _base_stats;
    const int           _rarity;
    Sprite*             _sprite;

    static std::map<std::string, ItemType*> all_types;
};

// An instance of an item with a type
class Item {
public:
    // Create a new Item
    Item(ItemType* type = nullptr, int level = 1, StatList stats = StatList()) : _type(type), _level(level), _stats(stats) {}
    ~Item() {}

    // Get this item's level
    inline unsigned int level()                     { return _level; }
    // Improve the stats of the item by bonus
    inline Item* upgrade(StatList bonus = StatList())   { return _stats += bonus, this; }
    // Increase the level of the item
    inline Item* level_up()                         { return ++_level, this; }

    inline StatList base_stats()    { return _type->base_stats(); }
    inline StatList bonus_stats()   { return _stats; }
    inline StatList total_stats()   { return _stats + _type->base_stats(); }

    inline ItemType* type() const   { return _type; }

    friend std::ostream& operator<<(std::ostream& out, const Item& item);
private:
    ItemType*       _type;
    unsigned int    _level;
    StatList        _stats;
};

// A collection of one type of item
class ItemStack {
public:
    // Create a new ItemStack
    ItemStack(ItemType* type = nullptr);
    ~ItemStack();
    // Reset this stack, and change it's type to t
    void reset(ItemType* t);

    inline ItemType* type() const       { return _type; }
    inline unsigned int length() const  { return _length; }
    inline Item* first() const          { return _items[0]; }
    inline Item* last()  const          { return _items[_length - 1]; }
    inline bool full() const            { return _type != nullptr && _length == _type->max_stack(); }

    /* Returns the level of the lowest levelled Item in the stack */
    unsigned int min_level() const;
    /* Returns the level of the highest levelled Item in the stack */
    unsigned int max_level() const;

    /*
        Removes the given Item from the stack.
        Returns the Item removed, or nullptr if the item was not found
    */
    Item* remove(Item* item);

    /*
        Removes the Item at the given index in the stack.
        Returns the Item removed, or nullptr if the item was not found.
    */
    Item* remove(const unsigned int index);

    /*
        Removes a substack of the ItemStack.
        Returns the removed substack as a new ItemStack.
    */
    ItemStack splice(const unsigned int start, const unsigned int length);

    /*
        Merges the contents of two ItemStacks, emptying the second
        Returns the remainder of the second stack, which is possibly empty or the whole stack
    */
    bool operator+=(ItemStack&);

    /*
        Adds an Item to the ItemStack.
        Returns true on success, false on failure
    */
    bool operator<<(Item*);
    /*
        Adds an Item or multiple items to the ItemStack, with the given level and stats.
        Returns the number of items that weren't added
    */
    int add(ItemType* type, const unsigned int amount = 1, const unsigned int level = 1, const StatList stats = StatList());

    inline Item* operator[](const unsigned int i) const { return i < _length ? _items[i] : nullptr; }

    friend std::ostream& operator<<(std::ostream& out, const ItemStack& stack);
private:
    ItemType*   _type;
    Item* *     _items;

    unsigned int _length = 0;

    /* Sorts the list in order of decreasing levels, with all nullptrs at the end */
    void _sort();
};

// A collection of stacks of items of various types
class Inventory {
public:
    // Create a new Inventory with the given number of slots
    Inventory(int slot_count) : _length(slot_count), _slots(new ItemStack[slot_count]) { sort.inv = this; }
    ~Inventory() { delete[] _slots; }

    // Get the total number of stacks with the given type in the inventory
    int count(ItemType* type) const;
    // Get the total number of items in all stacks in the inventory with the given type
    int count_individual(ItemType* type) const;

    // Find the first stack of the given type (going forward from start)
    int find(ItemType* type, const int start = 0) const;
    // Find the first stack of the given type (going back from start)
    int r_find(ItemType* type, const int start = 0) const;

    inline unsigned int length() const { return _length; }

    /* Merge all stacks of the same type into one (if possible) */
    void merge();

    /* Provides a number of sorting functions for different orders. */
    struct InventorySorter {
        Inventory* inv;

        /* Sort function to sort in alphabetical order */
        void alphabetical();

        /* Sort function to sort in descending order of (total) quantity. Alphabetical if they are equal */
        void count();

        /* Sort by kind of item, optionally offset to have another ItemKind be first. */
        void kind(const unsigned int first = 0);

        /* Sort function to separate out false ItemStacks */
        void exist();

        /* Sort by custom function */
        template<typename SortFunction>
        inline void custom(SortFunction f) { _sort(f); }
    private:
        bool _null(const unsigned int&) const;
        bool _alphabet(const unsigned int&, const unsigned int&) const;
        bool _stack_size(const unsigned int&, const unsigned int&) const;
        bool _stack_level(const unsigned int&, const unsigned int&) const;
        int _inv_count(const unsigned int&, const unsigned int&) const;
        int _kind(const unsigned int&, const unsigned int&, const int = 0) const;

        template<typename SortFunction>
        // Do the sorting based on the given function
        void _sort(SortFunction);
    } sort;

    // Pointer to the first stack
    inline ItemStack* begin() const { return _slots; }
    // Pointer to the last stack
    inline ItemStack* end() const { return _slots + _length; }

    inline ItemStack& operator[](const unsigned int i) const { return _slots[i]; }

    int add(ItemType*, const unsigned int = 1, const unsigned int = 1, const StatList = StatList());

    // Add an item to the inventory
    Inventory& operator<<(Item* item);
    // Add a stack of items to the inventory
    Inventory& operator<<(ItemStack& stack);

    friend std::ostream& operator<<(std::ostream& out, const Inventory& inv);
private:
    ItemStack * _slots;
    const unsigned int _length;
};

template<typename SortFunction>
void Inventory::InventorySorter::_sort(SortFunction ok) {
    inv->merge();
    //Make a list of locations
    unsigned int * locations = new unsigned int[inv->_length];
    for (unsigned int i = 0; i < inv->_length; i++) {
        locations[i] = i;
    }
    util::quicksort<unsigned int>(locations, inv->_length, ok);
    /*{
        std::function<void(unsigned int*, unsigned int)> qs;
        (qs = [this, &ok, &qs] (unsigned int * part, unsigned int len) -> void {
            unsigned int * left = new unsigned int[len - 1];
            unsigned int * right = new unsigned int[len - 1];
            unsigned int il = 0, ir = 0;
            unsigned int pivot = part[len - 1];
            for (unsigned int i = 0; i < len - 1; i++) {
                if (ok(inv->_slots + part[i], inv->_slots + pivot)) {
                    left[il++] = part[i];
                } else {
                    right[ir++] = part[i];
                }
            }
            if (il > 1) { qs(left, il); }
            if (ir > 1) { qs(right, ir); }
            for (unsigned int i = 0; i < len; i++) {
                if (i < il) {
                    part[i] = left[i];
                } else if (i == il) {
                    part[i] = pivot;
                } else {
                    part[i] = right[i - il - 1];
                }
            }
            delete[] left;
            delete[] right;
        })(locations, inv->_length);
    }*/
    //Reorder real list's contents in the order of the locations
    ItemStack* oldSlots = inv->_slots;
    inv->_slots = new ItemStack[inv->_length];
    for (unsigned int i = 0; i < inv->_length; i++) {
        inv->_slots[i] += oldSlots[locations[i]];
    }
    delete[] locations;
    delete[] oldSlots;
}
