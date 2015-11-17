#pragma once

#include <map>
#include <string>
#include "types.h"
#include "image.h"

class Sprite {
public:
    static Sprite* get(const std::string&, Image* = NULL) { return new Sprite("default", Image::get("default")); };

    ~Sprite() {}
private:
    Sprite(const std::string&, Image* i) : _image(i) {}

    std::string _name;
    Image* _image;
    Point _origin;
    Rect* _frames;
    Rect _stretch;

    static const std::map<std::string, Sprite*> all_sprites;
};