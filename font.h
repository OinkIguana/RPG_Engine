#pragma once

#include <SDL.h>
#include <SDL_TTF.h>
#include <fstream>
#include <string>
#include <map>
#include "draw.h"
#include "types.h"

class Font {
public:
    static Font* get(const std::string& = "default");
    static Font* get(const std::string&, const unsigned int& size, const std::string& = "");
    ~Font();

    static void import(const std::string&);
    void draw(const Point&, const std::string&, const unsigned int&) const;
    SDL_Surface* to_surface(const std::string&, const unsigned int&) const;
    inline void dimensions(std::string t, int& w, int& h) const { TTF_SizeText(_font, t.c_str(), &w, &h); }
private:
    Font(const std::string name, const unsigned int size, const std::string file);
    const std::string _name;
    const std::string _file;
    TTF_Font* _font;

    static std::map<std::string, Font*> all_fonts;
};