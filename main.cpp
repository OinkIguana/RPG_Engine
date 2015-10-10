// #include "engine.h"

#include "inventory.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    Stat::import("test.stats");
    ItemType::import("test.items");

    ItemType* apple = ItemType::get("Apple");
    
    std::cout << apple->base_stats() << std::endl;

    Item* ap = new Item(apple);
    ap->level_up()->upgrade(StatList("HP+:3"));

    std::cout << *ap << std::endl;
    std::cout << ap->total_stats() << std::endl;

    Inventory a(15);

    ItemStack s;
    s << new Item(apple);
    a << s;
    a << new Item(apple);
    
    ItemStack t;
    t << ap;
    t.add(apple, 5, 4, StatList("HP+:30"));
    a[1] += t;
    a[1].add(apple, 2, 3);
    a[1].remove(ap);
    a[1].remove(3);

    a.add(ItemType::get("Sword"), 3);
    a[6].add(apple, 15, 9);

    a.merge();

    {
        Item* sh = new Item(ItemType::get("Shield"));
        a << sh;
    }

    a << new Item(ItemType::get("Map"));
    a[8] += a[0];

    a.sort.kind(3);

    std::cout << a << std::endl;

	system("PAUSE");

	return 0;
}