#include "background.h"
#include "rpg.h"

std::map<std::string, Background*> Background::all_backgrounds = std::map<std::string, Background*>();

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

Background::Background(const unsigned int& n, Tile** tiles, const int& depth) : _depth(depth) {
    _pos = tiles[0]->pos();
    // Get the final dimensions/position of the background
    for (unsigned int i = 0; i < n; i++) {
        _pos = _pos | tiles[i]->pos();
    }
    _img = Image::compose(n, tiles);
    _name = "room_" + std::to_string(_depth);
    all_backgrounds[_name] = this;
}

Background::~Background() {
    if(_name.substr(0, 4) == "room") {
        delete _img;
    }
    all_backgrounds.erase(_name);
}

void Background::remove_room_bgs() {
    for (auto i = all_backgrounds.begin(); i != all_backgrounds.end();) {
        if (i->first.substr(0, 4) == "room") {
            delete (i++)->second;
        } else {
            ++i;
        }
    }
}

Background** Background::get_room_bgs(unsigned int* count) {
    auto i = all_backgrounds.begin();
    Background ** list;
    unsigned int n = 0;
    std::function<void(void)> next;
    (next = [&] {
        if (i == all_backgrounds.end()) {
            list = new Background*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        bool is = false;
        if (i->first.substr(0, 4) == "room") {
            n++;
            is = true;
        }
        ++i;
        next();
        --i;
        if (is) {
            list[--n] = i->second;
        }
    })();
    return list;
}

void Background::draw() const {
    if (_visible) {
        _img->draw(_pos, _depth);
    }
}
