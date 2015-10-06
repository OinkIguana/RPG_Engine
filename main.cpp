#include "engine.h"
#include "inventory.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    Stat::import("test.stats");
    ItemType::get("Apple", "Delicious", 10, 5, 99, 0, 0, 0, StatList::from_string("Heal:10"));
    Inventory a(15);
    Inventory b(15);
	system("PAUSE");
	return 0;
}