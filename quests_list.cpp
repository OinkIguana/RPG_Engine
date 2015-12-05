#include "progress.h"

void Progress::import() {
    Progress::add_storyline(new Storyline(
        "Cat Quest", 1,
        Quest("Get apples", "Get 3 apples for the cat")));
}