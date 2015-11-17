#pragma once

#include <map>
#include <string>
#include <fstream>
#include <functional>
#include "types.h"
#include "image.h"

class Sprite {
public:
    static Sprite* get(const std::string&, Image* = NULL);

    void set_frames(const Rect&);
    void set_frames(const Rect&, const Rect&);
    void set_frames(const Rect&, const Point&);
    void set_frames(const Rect&, const Rect&, const Point&);
    void set_frames(const unsigned int&, Rect*);

    inline Rect frame(const unsigned int& i) const { return _frames[i]; }
    inline unsigned int frames() const { return _frame_count; }

    void draw(const Point&, const unsigned int&);

    ~Sprite();
    static void import(const std::string&);
private:
    Sprite(const std::string&, Image* i);

    const std::string _name;
    const Point _origin;
    Image* _image;
    Rect* _frames;
    unsigned int _frame_count;

    static std::map<std::string, Sprite*> all_sprites;
};