#include "formatstring.h"
#include "rpg.h"
#include <iomanip>

std::map<char, unsigned int> FormatString::_color_map;
std::map<char, Font*> FormatString::_font_map;

FormatString::FormatString(const std::string& raw, const int& width) : _raw(raw), _width(width) {
    std::function<void(const unsigned int, const unsigned int)> next;
    Font* font_prev = Font::get();
    unsigned int col_prev = 0x000000;
    unsigned int line_y = 0;
    unsigned int line_x = 0;
    unsigned int max_width = 0;
    unsigned int chunk_start = 0;
    std::string prev_chunk = "";
    (next = [&](const unsigned int start, const unsigned int iteration) {
        _Piece* piece = new _Piece();
        piece->color = col_prev;
        piece->font = font_prev;
        piece->text = "";
        piece->x = line_x;
        piece->y = line_y;
        prev_chunk = "";
        bool escape = false, color = false, font = false;
        unsigned int i = start, delay = 0;
        chunk_start = i;
        for (i; i < _raw.length(); i++) {
            //Font and color can be set if no text has been collected yet
            if (color) {
                auto found = _color_map.find(_raw[i]);
                piece->color = (found != _color_map.end() ? found->second : 0x000000);
                col_prev = piece->color;
                color = false;
                continue;
            }
            if (font) {
                auto found = _font_map.find(_raw[i]);
                piece->font = (found != _font_map.end() ? found->second : Font::get());
                font_prev = piece->font;
                font = false;
                continue;
            }

            //Escaped things
            if (escape) {
                _text += _raw[i];
                escape = false;
                continue;
            }

            //Catch special characters
            switch (_raw[i]) {
            case '\n': //Add a line, and start a new piece
                line_x = 0;
                line_y = _height;
                i++;
                goto next_piece;
                break;
            case '\\': //Escape the next character
                escape = true;
                break;
            case FormatString::SYM::VAR: /* skip var char */ break;
            case FormatString::SYM::WAIT:
                if (piece->text.length() != 0) {
                    goto next_piece;
                }
                ++delay;
                ++_total_wait;
                break;
            case FormatString::SYM::COLOR:
                if (piece->text.length() != 0) {
                    goto next_piece;
                }
                color = true;
                break;
            case FormatString::SYM::FONT:
                if (piece->text.length() != 0) {
                    goto next_piece;
                }
                font = true;
                break;
            case ' ': //Move the word wrap point forward
            case '-':
                prev_chunk = piece->text;
                chunk_start = i + 1;
            default: //Regular characters
                _text += _raw[i];
                piece->text += _raw[i];
            }
            int width, height;
            piece->font->dimensions(piece->text, width, height);
            _height = std::max(_height, line_y + height);
            if (_width != -1 && piece->x + width > _width) {
                //Wrap words when they get too long
                i = chunk_start;
                piece->text = prev_chunk;
                line_x = 0;
                line_y = _height;
                goto next_piece;
            } else {
                line_x = piece->x + width;
            }
        }
    next_piece:
        //Record total width and previous width for word-wrapping
        int width, height;
        piece->font->dimensions(piece->text, width, height);
        max_width = std::max(max_width, piece->x + width);
        if (i != _raw.length()) {
            next(i, iteration + 1);
        } else {
            _pieces = new FormatString::_Piece*[iteration + 1];
            _length = iteration + 1;
        }
        _pieces[iteration] = piece;
    })(0, 0);
    _width = max_width;
}

FormatString::~FormatString() {
    for (unsigned int i = 0; i < _length; i++) { delete _pieces[i]; }
    delete[] _pieces;
    SDL_DestroyTexture(_tex);
}

void FormatString::draw(const Point& pos, const int& depth) {
    if (_tex == NULL) {
        SDL_Surface* surf = SDL_CreateRGBSurface(0, _width, _height, 32, RMASK, GMASK, BMASK, AMASK);
        for (unsigned int i = 0; i < _length; i++) {
            try {
                SDL_Surface* piece = _pieces[i]->font->to_surface(_pieces[i]->text, _pieces[i]->color);
                SDL_Rect pos = Rect(_pieces[i]->x, _pieces[i]->y, piece->w, piece->h);
                SDL_BlitSurface(piece, NULL, surf, &pos);
                SDL_FreeSurface(piece);
            } catch (int) {};
        }
        _tex = SDL_CreateTextureFromSurface(RPG::game_renderer(), surf);
        SDL_FreeSurface(surf);
    }
    draw::texture(pos, depth, _tex);
}

void FormatString::draw_upto(const unsigned int& end, const Point& pos, const int& depth) {
    if (end == _text.length()) return draw(pos, depth);
    SDL_Surface* surf = SDL_CreateRGBSurface(0, _width, _height, 32, RMASK, GMASK, BMASK, AMASK);
    std::string raw = "";
    std::string text = "";
    for (unsigned int i = 0; i < _length; i++) {
        std::string seg = "";
        while (seg.length() < _pieces[i]->text.length() && text.length() < end) {
            seg += _text[text.length()];
            text += _text[text.length()];
            do {
                raw += _raw[raw.length()];
            } while (_raw[raw.length()] != _text[text.length()]);
        }
        if (seg != "") {
            try {
                SDL_Surface* piece = _pieces[i]->font->to_surface(seg, _pieces[i]->color);
                SDL_Rect pos { (int)_pieces[i]->x, (int)_pieces[i]->y, piece->w, piece->h };
                SDL_BlitSurface(piece, NULL, surf, &pos);
                SDL_FreeSurface(piece);
            } catch (int) {};
        } else {
            break;
        }
    }
    draw::surface(pos, depth, surf);
    SDL_FreeSurface(surf);
}

FormatString FormatString::upto(const unsigned int& count) const {
    std::string raw = "";
    std::string text = "";
    while (text.length() < count) {
        text += _text[text.length()];
        do {
            raw += _raw[raw.length()];
        } while (_raw[raw.length()] != _text[text.length()]);
    }
    return FormatString(raw);
}

FormatString FormatString::operator<<(const int& v) const {
    auto i = _raw.find_first_of(SYM::VAR);
    if (i == std::string::npos) {
        return *this;
    } else {
        return FormatString(_raw.substr(0, i) + std::to_string(v) + _raw.substr(i + 1));
    }
}

FormatString FormatString::operator<<(const std::string& v) const {
    auto i = _raw.find_first_of(SYM::VAR);
    if (i == std::string::npos) {
        return *this;
    } else {
        return FormatString(_raw.substr(0, i) + v + _raw.substr(i + 1));
    }
}

void FormatString::import(const std::string path) {
    std::ifstream file(path);
    while (!file.eof()) {
        char t, s;
        file >> t;
        if (t == 'c') {
            int v;
            file >> s >> std::hex >> v;
            add_color(s, v);
        } else if (t == 'f') {
            std::string v;
            file >> s >> v;
            add_font(s, Font::get(v));
        }
    }
}
