#include "image.h"
#include "rpg.h"
#include <iostream>

std::map<std::string, Image*> Image::all_images = std::map<std::string, Image*>();

Image* Image::get(const std::string& name, const std::string& file) {
    auto old = all_images.find(name);
    if (old != all_images.end()) {
        return old->second;
    } else if(file != "") {
        all_images[name] = new Image(name, file);
        return all_images[name];
    }
    return nullptr;
}

void Image::draw(const Point& dest, const Rect& src) const {
    draw::texture_part(dest, _tex, src);
}
void Image::draw(const Point& dest) const {
    draw::texture(dest, _tex);
}

void Image::import(const std::string& path) {
    std::ifstream file(path);
    while (!file.eof()) {
        std::string name, url;
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
        //Add the font
        get(name, url);
    }
}

Image::Image(const std::string& name, const std::string& file) : _name(name), _file("resource/image/" + file) {
    SDL_Surface* surf = IMG_Load(_file.c_str());
    if (surf == NULL) {
        std::cout << "1: " << SDL_GetError() << std::endl;
        throw 1;
    }
    _tex = SDL_CreateTextureFromSurface(RPG::game_renderer(), surf);
    if (_tex == NULL) {
        std::cout << "2: " << SDL_GetError() << std::endl;
        throw 2;
    }
    SDL_FreeSurface(surf);
    std::cout << _tex << std::endl;
}

Image::~Image() {
    SDL_DestroyTexture(_tex);
    all_images.erase(_name);
}
