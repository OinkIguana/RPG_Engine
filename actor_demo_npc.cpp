#include "actor_demo_npc.h"
#include "rpg.h"

void QuestCat::_on_talk() {
    Player* player = against<Player>();
    if (player) {
        Storyline* storyline = Progress::get("Cat Quest");
        if (!storyline->quest(0).started()) {
            _dialog = Dialog::get("CatQuest.before");
            storyline->quest(0).start();
        } else {
            if (!storyline->done()) {
                if (player->inventory().count_individual(ItemType::get("Apple")) >= 3) {
                    _dialog = Dialog::get("CatQuest.end");
                    if (!storyline->quest(0).finished()) {
                        storyline->quest(0).finish();
                        delete player->inventory().remove(ItemType::get("Apple"), 3);
                    }
                } else {
                    _dialog = Dialog::get("CatQuest.during");
                }
            } else {
                _dialog = Dialog::get("CatQuest.after");
            }
        }
    }
}
