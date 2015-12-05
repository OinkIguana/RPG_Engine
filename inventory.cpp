#include "inventory.h"

std::map<std::string, ItemType*> ItemType::all_types;

ItemType * ItemType::get(   const std::string name, const std::string desc,
                            const int buy, const int sell, const unsigned int stack,
                            const unsigned int attributes, const unsigned int kind, const unsigned int rarity,
                            const StatList base_stats, Sprite* sprite) {
    auto old = all_types.find(name);
    if (old == all_types.end()) {
        all_types[name] = new ItemType(name, desc, buy, sell, stack, attributes, kind, rarity, base_stats, sprite);
        return all_types[name];
    } else {
        return old->second;
    }
}

void ItemType::import(const std::string fname) {
    std::ifstream file(fname);

    std::string name = "", desc = "";
    int buy = 0, sell = 0, max_stack = 0, attributes = 0, kind = 0, rarity = 0;
    Sprite* sprite = nullptr;
    StatList base_stats;
    std::map<std::string, int> constants;

    std::string line;
    do {
        std::getline(file, line);
        if (line[0] == '[') {
            if (name != "") {
                ItemType::get(name, desc, buy, sell, max_stack, attributes, kind, rarity, base_stats, sprite);
                desc = "";
                buy = 0, sell = 0, max_stack = 0, attributes = 0, kind = 0, rarity = 0;
                sprite = nullptr;
                base_stats = StatList();
            }
            name = line.substr(1, line.find(']') - 1);
            continue;
        }
        int eqpos;
        if((eqpos = line.find('=')) != std::string::npos) {
            std::string value = line.substr(eqpos + 1);
            if (name == "") {
                if (value[0] == '|') {
                    constants[line.substr(0, eqpos)] = std::stoi(value.substr(1), nullptr, 2);
                } else {
                    constants[line.substr(0, eqpos)] = std::stoi(value);
                }
                continue;
            }
            if (line.substr(0, eqpos) == "stats") {
                base_stats.read(value);
                continue;
            }
            switch (line[0]) {
            case 'd':
                desc = value;
                break;
            case 'b':
                buy = std::stoi(value);
                break;
            case 's':
                sell = std::stoi(value);
                break;
            case 'm':
                max_stack = std::stoi(value);
                break;
            case 'a':
                do {
                    int end = value.find('|');
                    if (end != std::string::npos) {
                        attributes |= constants[value.substr(0, end)];
                        value = value.substr(end + 1);
                    } else {
                        attributes |= constants[value];
                        value = "";
                    }
                } while (value != "");
                break;
            case 'k':
                kind = constants[value];
                break;
            case 'r':
                rarity = std::stoi(value);
                break;
            case 'i':
                sprite = Sprite::get(value);
                break;
            }
        }
    } while (!file.eof());
    if (name != "") {
        ItemType::get(name, desc, buy, sell, max_stack, attributes, kind, rarity, base_stats);
    }
}

bool ItemStack::operator+=(ItemStack& o) {
    if (o._type == nullptr || o._length == 0 || full()) {
        //If the stack to be added is false, or the stack added to is full, fail
        return false;
    }
    if (_type == nullptr) {
        //Allow adding to false stacks
        reset(o.type());
    }
    if (_type == o._type) {
        //If the types are the same
        const unsigned int len = o._length;
        for (unsigned int i = 0; i < len; i++) {
            //Add all the items
            if (!full()) {
                _items[_length++] = o.remove(0U);
            } else if(min_level() < o.max_level()) {
                _sort();
                //Replace the lowest level item
                Item* temp = remove(_length - 1);
                //With the highest level item
                _items[_length++] = o.remove(0U);
                o << temp;
            } else {
                break;
            }
        }
        _sort();
    }
    return o._length == 0;
}

int ItemStack::add(ItemType* type, const unsigned int amount, const unsigned int level, const StatList stats) {
    for (unsigned int i = 0; i < amount;  i++) {
        if (!(*this << new Item(type, level, stats))) {
            return amount - i;
        }
        if (full()) {
            return amount - i - 1;
        }
    }
    return 0;
}

void ItemStack::_sort() {
    if (_type == nullptr) { return; }
    std::sort(_items, _items + _type->max_stack(), [](Item* a, Item* b) {
        return (a == nullptr ? 0 : a->level()) > (b == nullptr ? 0 : b->level());
    });
}

bool ItemStack::operator<<(Item* o) {
    ItemStack t(o->type());
    t._items[t._length++] = o;
    return (*this) += t;
}

unsigned int ItemStack::min_level() const {
    if (_length == 0) { return 0; }
    unsigned int level = _items[0]->level();
    for (unsigned int i = 0; i < _length; i++) {
        if (_items[i]->level() < level) {
            level = _items[i]->level();
        }
    }
    return level;
}

unsigned int ItemStack::max_level() const {
    if (_length == 0) { return 0; }
    unsigned int level = _items[0]->level();
    for (unsigned int i = 0; i < _length; i++) {
        if (_items[i]->level() > level) {
            level = _items[i]->level();
        }
    }
    return level;
}

Item* ItemStack::remove(Item* o) {
    for (unsigned int i = 0; i < _length; i++) {
        if (_items[i] == o) {
            _items[i] = nullptr;
            _length--;
            if (_length) {
                _sort();
            } else {
                _type = nullptr;
            }
            return o;
        }
    }
    return nullptr;
}

Item* ItemStack::remove(unsigned int i) {
    Item* temp = nullptr;
    if (i < _length) {
        temp = _items[i];
        //Remove the item from the ItemStack, don't delete it
        _items[i] = nullptr;
        _length--;
        if (_length) {
            _sort();
        } else {
            _type = nullptr;
        }
    }
    return temp;
}

std::ostream& operator<<(std::ostream& out, const Item& i) {
    out << i.type()->name() << " Lv. " << i._level << " : " << i.type()->desc();
    return out;
}

ItemStack::ItemStack(ItemType* type) : _type(type), _items(new Item*[type == nullptr ? 1 : type->max_stack()]){
    const unsigned int len = (type == nullptr ? 1 : type->max_stack());
    for (unsigned int i = 0; i < len; i++) {
        _items[i] = nullptr;
    }
}

ItemStack::~ItemStack() {
    const unsigned int len = (_type == nullptr ? 1 : _type->max_stack());
    for (unsigned int i = 0; i < len; i++) {
        delete _items[i];
    }
    delete[] _items;
}

void ItemStack::reset(ItemType* t) {
    delete[] _items;
    _type = t;
    const unsigned int len = (_type == nullptr ? 1 : _type->max_stack());
    _items = new Item*[len];
    for (unsigned int i = 0; i < len; i++) {
        _items[i] = nullptr;
    }
}

ItemStack ItemStack::splice(const unsigned int start, const unsigned int length) {
    ItemStack part(_type);
    for (unsigned int i = 0; i < length; i++) {
        if (start >= _length) {
            break;
        }
        part << remove(start);
    }
    return part;
}

std::ostream& operator<<(std::ostream& out, const ItemStack& stack) {
    for (unsigned int i = 0; i < stack._length; i++) {
        if (stack[i] != nullptr) {
            out << *stack[i] << '\n';
        }
    }
    return out;
}

int Inventory::count(ItemType * t) const {
    int c = 0;
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() == t) {
            c++;
        }
    }
    return c;
}

int Inventory::count_individual(ItemType* t) const {
    unsigned int i = 0, c = 0;
    while ((i = find(t, i)) != _length) {
        c += _slots[i].length();
        i++;
    }
    return c;
}

int Inventory::find(ItemType* t, const unsigned int& start) const {
    for (unsigned int i = start; i < _length; i++) {
        if (_slots[i].type() == t) {
            return i;
        }
    }
    return _length;
}

int Inventory::r_find(ItemType * t, const unsigned int& start) const {
    for (int i = _length - start - 1; i >= 0; i--) {
        if (_slots[i].type() == t) {
            return i;
        }
    }
    return _length;
}

void Inventory::merge() {
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() != nullptr) {
            int j = i;
            while ((j = find(_slots[i].type(), j + 1)) != _length) {
                _slots[i] += _slots[j];
            }
        }
    }
}

int Inventory::add(ItemType* t, const unsigned int& amount, const unsigned int& level, const StatList& stats) {
    unsigned int a = amount, i = 0;
    while ((a = _slots[i++].add(t, a, level, stats)) && i < _length);
    return a;
}

ItemStack* Inventory::remove(ItemType* type, const unsigned int& amt, const unsigned int& level) {
    ItemStack* stack = new ItemStack(type);
    unsigned int i = 0;
    int ind = -1;
    while (i < amt && (ind = find(type, ind + 1)) != _length && !stack->full()) {
        while (i < amt && !_slots[ind].empty()) {
            if (_slots[ind][0]->level() >= level) {
                (*stack) << _slots[ind].remove(0u);
                i++;
            } else {
                break;
            }
        }
    }
    return stack;
}

Inventory &Inventory::operator<<(Item * o) {
    if (o == nullptr || o->type() == nullptr) {
        return *this;
    }
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() == o->type()) {
            if (_slots[i] << o) {
                return *this;
            }
        }
    }
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() == nullptr) {
            _slots[i] << o;
            break;
        }
    }
    return *this;
}

Inventory &Inventory::operator<<(ItemStack& o) {
    if (o.type() == nullptr) {
        return *this;
    }
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() == o.type()) {
            if (_slots[i] += o) {
                continue;
            }
            return *this;
        }
    }
    for (unsigned int i = 0; i < _length; i++) {
        if (_slots[i].type() == nullptr) {
            _slots[i] += o;
            break;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Inventory& inv) {
    for (unsigned int i = 0; i < inv._length; i++) {
        out << inv[i] << "------------------\n";
    }
    return out;
}

void Inventory::InventorySorter::alphabetical() {
    _sort([this](const unsigned int& a, const unsigned int& b) {
        return (!_null(a)) && (_null(b) || _alphabet(a, b) || _stack_size(a, b) || _stack_level(a, b));
    });
}

void Inventory::InventorySorter::count() {
    _sort([this](const unsigned int& a, const unsigned int& b) {
        if (_null(a)) { return false; }
        if (_null(b)) { return true; }
        int ic = _inv_count(a, b);
        if (ic != 0) { return ic > 0; }
        return _alphabet(a, b) || _stack_size(a, b) || _stack_level(a, b);
    });
}

void Inventory::InventorySorter::kind(const unsigned int first) {
    _sort([this, first](const unsigned int& a, const unsigned int& b) {
        if (_null(a)) { return false; }
        if (_null(b)) { return true; }
        int k = _kind(a, b, first);
        if (k != 0) { return k < 0; }
        return _alphabet(a, b) || _stack_size(a, b) || _stack_level(a, b);
    });
}

void Inventory::InventorySorter::exist() {
    _sort([this](const unsigned int& a, const unsigned int& b) {
        if (_null(a)) { return false; }
        if (_null(b)) { return true; }
        return true;
    });
}

bool Inventory::InventorySorter::_null(const unsigned int& a) const {
    return (inv->_slots + a)->type() == nullptr;
}

bool Inventory::InventorySorter::_alphabet(const unsigned int& a, const unsigned int& b) const {
    return (inv->_slots + a)->type()->name() < (inv->_slots + b)->type()->name();
}

bool Inventory::InventorySorter::_stack_size(const unsigned int& a, const unsigned int& b) const {
    return (inv->_slots + a)->length() > (inv->_slots + b)->length();
}

bool Inventory::InventorySorter::_stack_level(const unsigned int& a, const unsigned int& b) const {
    return (inv->_slots + a)->min_level() > (inv->_slots + b)->min_level();
}

int Inventory::InventorySorter::_inv_count(const unsigned int& a, const unsigned int& b) const {
    return inv->count_individual((inv->_slots + a)->type()) - inv->count_individual((inv->_slots + b)->type());
}

inline int Inventory::InventorySorter::_kind(const unsigned int& a, const unsigned int& b, const int first) const {
    int ka = (inv->_slots + a)->type()->kind(), kb = (inv->_slots + b)->type()->kind();
    if (kb == first) { return 1; }
    if (ka == first) { return -1; }
    if (ka < first && kb > first) { return 1; }
    if (ka > first && kb < first) { return -1; }
    return ka - kb;
}
