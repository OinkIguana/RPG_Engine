#include "image.h"
#include "rpg.h"

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

Image* Image::compose(const std::string& name, const unsigned int& n, Tile** tiles) {
    all_images[name] = new Image(name, n, tiles);
    return all_images[name];
}

Image* Image::compose(const unsigned int& n, Tile** tiles) {
    return new Image("temp", n, tiles);
}

void Image::draw(const Point& dest, const Rect& src, const int& depth) const {
    draw::texture_part(dest, depth, _tex, src);
}
void Image::draw(const Rect& dest, const Rect& src, const int& depth) const {
    draw::texture_part(dest, depth, _tex, src);
}
void Image::draw(const Point& dest, const int& depth) const {
    draw::texture(dest, depth, _tex);
}
void Image::draw(const Rect& dest, const int& depth) const {
    draw::texture(dest, depth, _tex);
}

void Image::copy_to_surface(SDL_Surface* surf, SDL_Rect& piece, SDL_Rect& pos) const {
    SDL_BlitSurface(_surf, &piece, surf, &pos);
}

void Image::import(const std::string& path) {
    std::ifstream file(path);
    while (!file.eof()) {
        std::string name, url;
        std::string seg;
        file >> name;
        file >> seg;
        seg.erase(0, 1); // Remove "
        while (seg.back() != '"') {
            //Go until the path ends
            if (url != "") { url += " "; }
            url += seg;
            file >> seg;
        }
        if (url != "") { url += " "; }
        url += seg.substr(0, seg.length() - 1);
        //Add the image
        get(name, url);
    }
}

Image::Image(const std::string& name, const std::string& file) : _name(name), _file("resource/image/" + file) {
    _surf = IMG_Load(_file.c_str());
    if (_surf == NULL) { throw 1; }
    _width = _surf->w;
    _height = _surf->h;
    _tex = SDL_CreateTextureFromSurface(RPG::game_renderer(), _surf);
    if (_tex == NULL) { throw 2; }
}

Image::Image(const std::string& name, const unsigned int& n, Tile** tiles) : _name(name) {
    Rect pos = tiles[0]->pos();
    for (unsigned int i = 0; i < n; i++) {
        pos = pos | tiles[i]->pos();
    }
    _surf = SDL_CreateRGBSurface(0, pos.w, pos.h, 32, RMASK, GMASK, BMASK, AMASK);
    if (_surf == NULL) { throw 1; }
    for (unsigned int i = 0; i < n; i++) {
        tiles[i]->copy_to_surface(_surf, -(Point)pos);
    }
    _tex = SDL_CreateTextureFromSurface(RPG::game_renderer(), _surf);
    if (_tex == NULL) { throw 2; }
}

Image::~Image() {
    SDL_DestroyTexture(_tex);
    SDL_FreeSurface(_surf);

    all_images.erase(_name);
}
