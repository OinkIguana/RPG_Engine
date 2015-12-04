#include "progress.h"

Quest Quest::nullquest = Quest([] (Quest*) { return false; }, [] (Quest*) {}, "[null quest]");
std::map<std::string, Storyline*> Progress::all_storylines;

Storyline::Storyline(const std::string& name, const unsigned int length, ...) : _name(name), _length(length) {
    va_list quests;
    va_start(quests, length);
    _quests = new Quest[length];
    for (unsigned int i = 0; i < length; i++) {
        _quests[i] = va_arg(quests, Quest);
    }
    va_end(quests);

    Progress::add_storyline(this);
}

void Progress::check() {
    for (auto i = all_storylines.begin(); i != all_storylines.end(); i++) {
        if (i->second->check()) {
            i->second->make_progress();
        }
    }
}
