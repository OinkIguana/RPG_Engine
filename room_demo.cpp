#include "room.h"

class RM_demo : public Room {
    friend class Room;
private:
    RM_demo() : Room("demo", 1024, 768) {}
    virtual void tiles() {
    }
    virtual void actors() {
        Actor::create<NPC>()->pos({256, 320});
        Actor::create<Player>()->pos({128, 320});
        Actor::create<Wall>()->pos({32, 160});
        Actor::create<Wall>()->pos({32, 192});
        Actor::create<Wall>()->pos({32, 224});
        Actor::create<Wall>()->pos({32, 288});
        Actor::create<Wall>()->pos({32, 256});
        Actor::create<Wall>()->pos({32, 320});
        Actor::create<Wall>()->pos({32, 384});
        Actor::create<Wall>()->pos({32, 352});
        Actor::create<Wall>()->pos({32, 416});
        Actor::create<Wall>()->pos({32, 480});
        Actor::create<Wall>()->pos({32, 448});
        Actor::create<Wall>()->pos({64, 480});
        Actor::create<Wall>()->pos({96, 480});
        Actor::create<Wall>()->pos({128, 480});
        Actor::create<Wall>()->pos({160, 480});
        Actor::create<Wall>()->pos({192, 480});
        Actor::create<Wall>()->pos({224, 480});
        Actor::create<Wall>()->pos({256, 480});
        Actor::create<Wall>()->pos({288, 480});
        Actor::create<Wall>()->pos({320, 480});
        Actor::create<Wall>()->pos({352, 480});
        Actor::create<Wall>()->pos({352, 448});
        Actor::create<Wall>()->pos({352, 416});
        Actor::create<Wall>()->pos({352, 384});
        Actor::create<Wall>()->pos({352, 352});
        Actor::create<Wall>()->pos({352, 320});
        Actor::create<Wall>()->pos({352, 288});
        Actor::create<Wall>()->pos({352, 256});
        Actor::create<Wall>()->pos({352, 224});
        Actor::create<Wall>()->pos({352, 192});
        Actor::create<Wall>()->pos({352, 160});
        Actor::create<Wall>()->pos({320, 160});
        Actor::create<Wall>()->pos({256, 160});
        Actor::create<Wall>()->pos({288, 160});
        Actor::create<Wall>()->pos({224, 160});
        Actor::create<Wall>()->pos({160, 160});
        Actor::create<Wall>()->pos({192, 160});
        Actor::create<Wall>()->pos({128, 160});
        Actor::create<Wall>()->pos({96, 160});
        Actor::create<Wall>()->pos({64, 160});
    }
};
