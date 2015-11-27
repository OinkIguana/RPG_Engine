#include "sprite.h"

std::map<std::string, Sprite*> Sprite::all_sprites = std::map<std::string, Sprite*>();

Sprite* Sprite::get(const std::string& name, Image* img) {
    auto old = all_sprites.find(name);
    if (old != all_sprites.end()) {
        return old->second;
    } else if(img != NULL) {
        all_sprites[name] = new Sprite(name, img);
        return all_sprites[name];
    } else {
        return nullptr;
    }
}

void Sprite::set_frames(const Rect& base) {
    delete[] _frames;
    Point off = { 0,0 };
    unsigned int n = 0;
    std::function<void()> next;
    (next = [&] {
        if ((unsigned)off.y + base.h <= _image->height()) {
            Rect frame = base >> off;
            if ((unsigned)off.x + base.w < _image->width()) {
                off.x += base.w;
            } else {
                off.x = 0;
                off.y += base.h;
            }
            ++n;
            next();
            _frames[--n] = frame;
        } else {
            _frame_count = n;
            _frames = new Rect[n];
        }
    })();
}

void Sprite::set_frames(const Rect& base, const Rect& bound) {
    delete[] _frames;
    Point off = { bound.x, bound.y };
    unsigned int n = 0;
    std::function<void()> next;
    (next = [&] {
        if (off.y + base.h <= bound.bot()) {
            Rect frame = base >> off;
            if (off.x + base.w < bound.rs()) {
                off.x += base.w;
            } else {
                off.x = bound.x;
                off.y += base.h;
            }
            ++n;
            next();
            _frames[--n] = frame;
        } else {
            _frame_count = n;
            _frames = new Rect[n];
        }
    })();
}

void Sprite::set_frames(const Rect& base, const Point& sep) {
    delete[] _frames;
    Point off = { 0,0 };
    unsigned int n = 0;
    std::function<void()> next;
    (next = [&] {
        if ((unsigned)(off.y + base.h) <= _image->height()) {
            Rect frame = base >> off;
            if ((unsigned)(off.x + base.w) < _image->width()) {
                off.x += sep.x;
            } else {
                off.x = 0;
                off.y += sep.y;
            }
            ++n;
            next();
            _frames[--n] = frame;
        } else {
            _frame_count = n;
            _frames = new Rect[n];
        }
    })();
}


void Sprite::set_frames(const Rect& base, const Rect& bound, const Point& sep) {
    delete[] _frames;
    Point off = { bound.x, bound.y };
    unsigned int n = 0;
    std::function<void()> next;
    (next = [&] {
        if (off.y + base.h <= bound.bot()) {
            Rect frame = base >> off;
            if (off.x + base.w < bound.rs()) {
                off.x += sep.x;
            } else {
                off.x = bound.x;
                off.y += sep.y;
            }
            ++n;
            next();
            _frames[--n] = frame;
        } else {
            _frame_count = n;
            _frames = new Rect[n];
        }
    })();
}

void Sprite::set_frames(const unsigned int& n, Rect* frames) {
    delete[] _frames;
    _frame_count = n;
    _frames = frames;
}

void Sprite::draw(const Point& pos, const unsigned int& fr, const int& depth) {
    _image->draw(pos, _frames[fr], depth);
}

void Sprite::import(const std::string& path) {
    std::ifstream file(path);
    while (!file.eof()) {
        std::string name, img;
        char field;
        int x, y, w, h, n = 0;
        file >> name >> img;
        Rect* frame = nullptr;
        Rect* bound = nullptr;
        Point* sep = nullptr;
        do {
            file >> field;
            switch (field) {
            case 'f':
                file >> x >> y >> w >> h;
                frame = new Rect(x, y, w, h);
                break;
            case 'b':
                file >> x >> y >> w >> h;
                bound = new Rect(x, y, w, h);
                break;
            case 's':
                file >> x >> y;
                sep = new Point(x, y);
                break;
            case 'n':
                file >> n;
                frame = new Rect[n];
                for (int i = 0; i < n; i++) {
                    file >> x >> y >> w >> h;
                    frame[i] = Rect(x, y, w, h);
                }
            }
        } while (field != 'x');

        Sprite* spr = Sprite::get(name, Image::get(img));
        if (n != 0) {
            spr->set_frames(n, frame);
        } else if (frame != nullptr) {
            if (bound == nullptr) {
                if (sep == nullptr) {
                    spr->set_frames(*frame);
                } else {
                    spr->set_frames(*frame, *sep);
                }
            } else {
                if (sep == nullptr) {
                    spr->set_frames(*frame, *bound);
                } else {
                    spr->set_frames(*frame, *bound, *sep);
                }
            }
        }

        delete frame;
        delete bound;
        delete sep;
    }
}

Sprite::Sprite(const std::string &, Image * i) : _image(i) {
    _frames = new Rect[1];
    _frames[0] = Rect(0, 0, _image->width(), _image->height());
}


Sprite::~Sprite() {
    delete[] _frames;
    all_sprites.erase(_name);
}
