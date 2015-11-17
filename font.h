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
    // Get the font with the given name, or the default font if no name is provided
    static Font* get(const std::string& name = "default");
    // Get the font with the given name, or create it with the size and file given
    static Font* get(const std::string& name, const unsigned int& size, const std::string& url);
    ~Font();

    /* Load fonts from a file in the form of:
    *  ==========
    *  fontname "path/to/file.ttf" size
    *  fontname2 "path/to/file2.ttf" size
    *  ==========
    */
    static void import(const std::string& path);
    // Draw text at the point in the color
    void draw(const Point& pos, const std::string& text, const unsigned int& color) const;
    // Create a surface containing the text in the color, but don't draw it
    SDL_Surface* to_surface(const std::string& text, const unsigned int& col) const;
    // Get the dimensions of the text if it were drawn in this font
    inline void dimensions(std::string t, int& w, int& h) const { TTF_SizeText(_font, t.c_str(), &w, &h); }
private:
    // Load the font from the file
    Font(const std::string name, const unsigned int size, const std::string file);
    const std::string _name;
    const std::string _file;
    TTF_Font* _font;

    static std::map<std::string, Font*> all_fonts;
};