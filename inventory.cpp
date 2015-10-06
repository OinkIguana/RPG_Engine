#include "inventory.h"

ItemType * ItemType::get(   const std::string name, const std::string desc,
                            const int buy, const int sell, const unsigned int stack,
                            const unsigned int attributes, const unsigned int kind, const unsigned int rarity,
                            const StatList base_stats) {
	auto old = all_types.find(name);
	if (old == all_types.end()) {
		all_types[name] = new ItemType(name, desc, buy, sell, stack, attributes, kind, rarity, base_stats);
		return all_types[name];
	} else {
		return old->second;
	}
}

void ItemType::import(const std::string fname) {
    std::ifstream file(fname);

    std::string name = "", desc = "";
    int buy = 0, sell = 0, max_stack = 0, attributes = 0, kind = 0, rarity = 0;
    StatList base_stats;
    std::map<std::string, int> constants;

    std::string line;
    do {
        std::getline(file, line);
        if (line[0] == '[') {
            if (name != "") {
                ItemType::get(name, desc, buy, sell, max_stack, attributes, kind, rarity, base_stats);
            }
            name = line.substr(1, line.find(']') - 1);
            continue;
        }
        int eqpos;
        if((eqpos = line.find('=')) != std::string::npos) {
            std::string value = line.substr(eqpos + 1);
            if (name == "") {
                if (value[0] == '|') {
                    constants[line.substr()] = std::stoi(value.substr(1), nullptr, 2);
                } else {
                    constants[line.substr()] = std::stoi(value);
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
                    int v = constants[value.substr(0, value.find('|'))];
                    attributes |= v;
                } while ((value = value.substr(value.find('|') + 1)) != "");
                break;
            case 'k':
                kind = constants[value];
                break;
            case 'r':
                rarity = std::stoi(value);
                break;
            }
        }
    } while (!file.eof());
}

ItemStack ItemStack::operator+=(ItemStack& o) {
	if (!o) {
        //If the stack is false, return it immediately
        return o;
	}
	if (_type == nullptr) {
        //Allow adding to false stacks
		_type = o._type;
		delete[] _items;
		_items = new Item*[_type->_max_stack];
	}
    if (_type == o._type) {
        //If the types are the same
        for (int i = 0; i < o._length; i++) {
            //Add all the items
            _items[_length++] = o.remove(i);
            if (full()) {
                //If the stack has been filled, clean and return the rest of the one being taken from
                o.sort();
                break;
            }
        }
        sort();
    } //Return the entire other stack if it was not addable
	return o;
}

ItemStack ItemStack::operator+=(Item* o) {
	if (!*o || o == nullptr) {
		//If the item doesn't actually exist, return a false stack
		return ItemStack();
	}
	if (!*this) {
		//Allow adding to false stacks
		_type = o->type();
		delete[] _items;
		_items = new Item*[_type->_max_stack];
	}
	if (o->type() != _type && _length < _type->_max_stack) {
		//If it could be added, add it
		_items[_length++] = o;
		sort();
		return ItemStack();
	} else {
		//If it couldn't be added, make a new stack with the one item
		ItemStack second(o->type());
		second += o;
		return second;
	}
}

Item* ItemStack::remove(Item* o) {
	for (int i = 0; i < _length; i++) {
		if (_items[i] == o) {
			_items[i] = nullptr;
			_length--;
            if (_length) {
                sort();
            } else {
                //Delete the pointers to the pointers to the Items (not the Items)
                _type = nullptr;
                delete[] _items;
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
            sort();
		} else {
            //Delete the pointers to the pointers to the Items (not the Items)
            _type = nullptr;
            delete[] _items;
		}
	}
	return temp;
}

ItemStack ItemStack::slice(const int start, const int length) const {
	ItemStack part(_type);
	for (unsigned int i = 0; i < length; i++) {
		if (start + i >= _length) {
			break;
		}
		part += _items[start + i];
	}
	return part;
}


ItemStack ItemStack::splice(const int start, const int length) {
	ItemStack part(_type);
	for (unsigned int i = 0; i < length; i++) {
		if (start >= _length) {
			break;
		}
		part += remove(start);
	}
	return part;
}

int Inventory::count(ItemType * t) const {
    int c = 0;
    for (int i = 0; i < _length; i++) {
        if (_slots[i].type() == t) {
            c++;
        }
    }
    return c;
}

int Inventory::count_individual(ItemType* t) const {
    int i = 0, c = 0;
    while ((i = find(t, i + 1)) != _length) {
        c += _slots[i].length();
    }
    return 0;
}

int Inventory::find(ItemType* t, const int start) const {
    for (int i = start; i < _length; i++) {
        if (_slots[i].type() == t) {
            return i;
        }
    }
    return _length;
}

int Inventory::r_find(ItemType * t, const int start) const {
    for (int i = _length - start - 1; i >= 0; i--) {
        if (_slots[i].type() == t) {
            return i;
        }
    }
    return _length;
}

inline void Inventory::merge() {
    for (int i = 0; i < _length; i++) {
        if (_slots[i]) {
            int j = i;
            while ((j = find(_slots[i].type()), j + 1) != _length) {
                _slots[i] += _slots[j];
                if(_slots[i].full()) {
                    break;
                }
            }
        }
    }
}
