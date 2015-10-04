#ifndef __RPG_INVENTORY_H__
#define __RPG_INVENTORY_H__

#include "stats.h"
#include <string>
#include <map>

enum { BUY, SELL };

static enum {
	CONSUMABLE	= 1<<0,
	REUSABLE	= 1<<1,
	EQUIPPABLE	= 1<<2,
	BATTLE		= 1<<3,
	KEY			= 1<<4
};

class ItemType {
public:
	ItemType() {}
	~ItemType() {}
private:
	std::string name;
	std::string desc;
	int price[2];
	int max_stack;
	int attributes;
	StatList base_stats;
};

class Item {
public:
	Item() {}
	~Item() {}
private:
	ItemType type;
	int level;
	StatList stats;
};

class Inventory {
public:
	Inventory(int slot_count) { slots = new slot[slot_count]; }
	~Inventory() {}
	typedef std::pair<ItemType*, Item*> slot;
private:
	slot * slots;
};

#endif