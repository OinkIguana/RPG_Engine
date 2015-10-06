//#include "engine.h"
#include "stats.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    Stat::import("test.stats");
    StatList x("Health:5,Defense:7,Bow:15");
    std::cout << x;
	system("PAUSE");
	return 0;
}