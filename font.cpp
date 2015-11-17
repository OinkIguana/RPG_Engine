#include "font.h"
#include <iostream>

std::map<std::string, Font*> Font::all_fonts = std::map<std::string, Font*>();

Font::Font(const std::string name, const unsigned int size, const std::string file) : _name(name), _file("resource/font/" + file) {
    _font = TTF_OpenFont(_file.c_str(), size);
}

Font::~Font() {
    TTF_CloseFont(_font);
    all_fonts.erase(_name);
}

Font* Font::get(const std::string& name) {
    auto old = all_fonts.find(name);
    if (old != all_fonts.end()) {
        return old->second;
    } else {
        return all_fonts["default"];
    }
}


Font* Font::get(const std::string& name, const unsigned int& size, const std::string& file) {
    auto old = all_fonts.find(name);
    if (old != all_fonts.end()) {
        return old->second;
    } else {
        all_fonts[name] = new Font(name, size, file);
        return all_fonts[name];
    }
}

void Font::import(const std::string& path) {
    std::ifstream file(path);
    while (!file.eof()) {
        std::string name, url;
        unsigned int size;
        std::string seg;
        file >> seg;
        do {
            if (name != "") { name += " "; }
            name += seg;
            file >> seg;
            // Go until the path is found
        } while (seg.front() != '"');
        seg.erase(0, 1); // Remove "
        while (seg.back() != '"') {
            //Go until the path ends
            if (url != "") { url += " "; }
            url += seg;
            file >> seg;
        }
        if (url != "") { url += " "; }
        url += seg.substr(0, seg.length() - 1);
        file >> size;
        //Add the font
        get(name, size, url);
    }
}

void Font::draw(const Point& pos, const std::string& text, const unsigned int& color) const {
    SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), Color::hex(color));
    if (surface == NULL) { throw 0; }
    draw::surface(pos, surface);
    SDL_FreeSurface(surface);
}
SDL_Surface* Font::to_surface(const std::string& text, const unsigned int& color) const {
    SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), Color::hex(color));
    if (surface == NULL) { throw 0; }
    return surface;
}