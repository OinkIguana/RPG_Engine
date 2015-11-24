#include "background.h"
#include "rpg.h"

std::map<std::string, Background*> Background::all_backgrounds = std::map<std::string, Background*>();
std::map<Image*, Background*> Background::temp_backgrounds = std::map<Image*, Background*>();

Background* Background::get(const std::string& name, Image* img, const Point& p, const int& depth) {
    auto old = all_backgrounds.find(name);
    if (old != all_backgrounds.end()) {
        return old->second;
    } else {
        if (img != nullptr) {
            all_backgrounds[name] = new Background(name, img, p, depth);
            return all_backgrounds[name];
        }
    }
    return nullptr;
}

Background::Background(const std::string& name, Image* img, const Point& p, const int& depth) : _name(name), _pos(p), _depth(depth) {}

Background::Background(const int& n, Tile** tiles, const int& depth) : _depth(depth) {
    {   // Get the final dimensions/position of the background
        std::function<Rect(Tile**, const unsigned int&)> merge;
        _pos = (merge = [&merge](Tile** tiles, const unsigned int& n) {
            return (n == 0) ? tiles[0]->pos() : tiles[n]->pos() | merge(tiles, n - 1);
        })(tiles, n - 1);
    }
    _img = Image::compose(n, tiles);
    temp_backgrounds[_img] = this;
}

Background::~Background() {
    if(_name == "temp") {
        temp_backgrounds.erase(_img);
        delete _img;
    } else {
        all_backgrounds.erase(_name);
    }
}

void Background::clear_temp() {
    temp_backgrounds.clear();
}

Background** Background::get_temps(unsigned int* count) {
    *count = temp_backgrounds.size();
    Background** list = new Background*[temp_backgrounds.size()];
    unsigned int i = 0;
    for (auto bg : temp_backgrounds) {
        list[i++] = bg.second;
    }
    return list;
}

void Background::draw() const {
    _img->draw(_pos);
}
