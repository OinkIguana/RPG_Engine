#include "room.h"

class RM_demo_inside : public Room {
    friend class Room;
private:
    RM_demo_inside() : Room("demo_inside", 1024, 1024) {}
    virtual void tiles() override {
        Background* bg[4];
        Tile * tiles_0[177] = {
            new Tile(Image::get("house"),
                    Point(64, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(288, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 256),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 288),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 224),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(128, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(192, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(256, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(224, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(320, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(384, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(416, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(448, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(480, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(512, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(544, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(576, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(608, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(640, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(672, 320),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(672, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(640, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(640, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(640, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(640, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(576, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(576, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(576, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(544, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(512, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(512, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(512, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(544, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(544, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(544, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(512, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(576, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(608, 352),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(608, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(608, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(96, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(192, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(224, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(256, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(288, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(128, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(160, 192),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(160, 96),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(352, 96),
                    Rect(128, 0, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 96),
                    Rect(96, 0, 32, 32)),
            new Tile(Image::get("house"),
                    Point(704, 224),
                    Rect(128, 0, 32, 32)),
            new Tile(Image::get("house"),
                    Point(384, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(416, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(448, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(480, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(512, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(544, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(576, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(608, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(640, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(352, 128),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 160),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 192),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(704, 256),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(704, 288),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(704, 320),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(704, 352),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 128),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 160),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 192),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 224),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 256),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 288),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 320),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(32, 352),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(672, 384),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(672, 416),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(672, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(64, 96),
                    Rect(0, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(320, 96),
                    Rect(64, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(672, 224),
                    Rect(64, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(352, 224),
                    Rect(32, 0, 32, 128)),
            new Tile(Image::get("house"),
                    Point(608, 448),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(544, 480),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(576, 480),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(608, 480),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(640, 544),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(608, 544),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(576, 512),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(544, 512),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(608, 512),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(640, 512),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(576, 544),
                    Rect(32, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(512, 480),
                    Rect(0, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(512, 512),
                    Rect(0, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(544, 544),
                    Rect(64, 0, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(512, 544),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(576, 576),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(608, 576),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(640, 576),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(544, 576),
                    Rect(0, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(672, 576),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(672, 544),
                    Rect(64, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(672, 480),
                    Rect(64, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(672, 512),
                    Rect(64, 96, 32, 32)),
            new Tile(Image::get("grass"),
                    Point(640, 480),
                    Rect(32, 96, 32, 32)),
        };
        bg[0] = new Background(177, tiles_0, 0);
        for(unsigned int i = 0; i < 177; i++) {
            delete tiles_0[i];
        }
        Tile * tiles_100[25] = {
            new Tile(Image::get("house"),
                    Point(64, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(96, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(128, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(160, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(192, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(256, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(320, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(224, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(288, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(512, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(544, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(672, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(352, 256),
                    Rect(96, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(480, 256),
                    Rect(128, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 288),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 320),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 352),
                    Rect(64, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(480, 288),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(480, 320),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(480, 352),
                    Rect(32, 128, 32, 32)),
            new Tile(Image::get("house"),
                    Point(352, 384),
                    Rect(128, 32, 32, 96)),
            new Tile(Image::get("house"),
                    Point(480, 384),
                    Rect(96, 32, 32, 96)),
            new Tile(Image::get("house"),
                    Point(576, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(640, 384),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(608, 416),
                    Rect(256, 0, 32, 64)),
        };
        bg[1] = new Background(25, tiles_100, 100);
        for(unsigned int i = 0; i < 25; i++) {
            delete tiles_100[i];
        }
        Tile * tiles_1[3] = {
            new Tile(Image::get("house"),
                    Point(352, 224),
                    Rect(96, 160, 32, 96)),
            new Tile(Image::get("house"),
                    Point(32, 384),
                    Rect(96, 32, 32, 96)),
            new Tile(Image::get("house"),
                    Point(704, 384),
                    Rect(128, 32, 32, 96)),
        };
        bg[2] = new Background(3, tiles_1, 1);
        for(unsigned int i = 0; i < 3; i++) {
            delete tiles_1[i];
        }
        Tile * tiles_99[6] = {
            new Tile(Image::get("house"),
                    Point(352, 256),
                    Rect(0, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(384, 256),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(416, 256),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(448, 256),
                    Rect(32, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(480, 256),
                    Rect(64, 0, 32, 96)),
            new Tile(Image::get("house"),
                    Point(608, 384),
                    Rect(32, 0, 32, 96)),
        };
        bg[3] = new Background(6, tiles_99, 99);
        for(unsigned int i = 0; i < 6; i++) {
            delete tiles_99[i];
        }
    }
    virtual void actors() override {
        Actor::create<Door>("demo_outside")->pos({608, 496});
        Actor::create<HelloCat>()->pos({256, 256});
        Actor::create<ByeCat>()->pos({640, 320});
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
        Actor::create<Wall>()->pos({352, 288});
        Actor::create<Wall>()->pos({352, 256});
        Actor::create<Wall>()->pos({352, 224});
        Actor::create<Wall>()->pos({352, 192});
        Actor::create<Wall>()->pos({352, 160});
        Actor::create<Wall>()->pos({320, 160});
        Actor::create<Wall>()->pos({256, 160});
        Actor::create<Wall>()->pos({288, 160});
        Actor::create<Wall>()->pos({224, 160});
        Actor::create<Wall>()->pos({128, 160});
        Actor::create<Wall>()->pos({96, 160});
        Actor::create<Wall>()->pos({64, 160});
        Actor::create<Wall>()->pos({160, 160});
        Actor::create<Wall>()->pos({192, 160});
        Actor::create<Wall>()->pos({1056, 192});
        Actor::create<Wall>()->pos({384, 288});
        Actor::create<Wall>()->pos({448, 288});
        Actor::create<Wall>()->pos({416, 288});
        Actor::create<Wall>()->pos({384, 352});
        Actor::create<Wall>()->pos({416, 352});
        Actor::create<Wall>()->pos({448, 352});
        Actor::create<Wall>()->pos({480, 288});
        Actor::create<Wall>()->pos({512, 288});
        Actor::create<Wall>()->pos({544, 288});
        Actor::create<Wall>()->pos({608, 288});
        Actor::create<Wall>()->pos({576, 288});
        Actor::create<Wall>()->pos({640, 288});
        Actor::create<Wall>()->pos({1056, 288});
        Actor::create<Wall>()->pos({672, 288});
        Actor::create<Wall>()->pos({704, 288});
        Actor::create<Wall>()->pos({704, 320});
        Actor::create<Wall>()->pos({704, 352});
        Actor::create<Wall>()->pos({704, 480});
        Actor::create<Wall>()->pos({672, 480});
        Actor::create<Wall>()->pos({640, 480});
        Actor::create<Wall>()->pos({576, 480});
        Actor::create<Wall>()->pos({544, 480});
        Actor::create<Wall>()->pos({512, 480});
        Actor::create<Wall>()->pos({480, 480});
        Actor::create<Wall>()->pos({480, 448});
        Actor::create<Wall>()->pos({480, 416});
        Actor::create<Wall>()->pos({480, 384});
        Actor::create<Wall>()->pos({480, 352});
        Actor::create<Wall>()->pos({704, 416});
        Actor::create<Wall>()->pos({704, 384});
        Actor::create<Wall>()->pos({704, 448});
        Actor::create<Wall>()->pos({32, 160});
        Actor::create<Wall>()->pos({32, 192});
        Actor::create<Wall>()->pos({32, 224});
        Actor::create<Wall>()->pos({32, 256});
        Actor::create<Wall>()->pos({32, 288});
        Actor::create<Wall>()->pos({32, 320});
        Actor::create<Wall>()->pos({32, 352});
        Actor::create<Wall>()->pos({32, 384});
        Actor::create<Wall>()->pos({32, 416});
    }
};
