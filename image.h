#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sdl.h>
#include <SDL_image.h>
#include "draw.h"
#include "types.h"

class Image {
public:
    static Image* get(const std::string&, const std::string& = "");
    ~Image();

    void draw(const Point&, const Rect&) const;
    void draw(const Point&) const;

    static void import(const std::string&);
private:
    Image(const std::string&, const std::string&);
    const std::string _name;
    const std::string _file;
    SDL_Texture* _tex;

    static std::map<std::string, Image*> all_images;
};