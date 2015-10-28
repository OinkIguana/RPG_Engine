#include "types.h"

Point Point::operator+(const Point o) const {
	return Point(x + o.x, y + o.y);
}
Point Point::operator-(const Point o) const {
	return Point(x - o.x, y - o.y);
}
Point Point::operator*(const int n) const {
	return Point(x * n, y * n);
}
Point Point::operator/(const int n) const {
	return Point(x / n, y / n);
}
Point Point::operator+=(const Point o) {
	x += o.x;
	y += o.y;
	return *this;
}
Point Point::operator-=(const Point o) {
	x -= o.x;
	y -= o.y;
	return *this;
}
Point Point::operator*=(const int n) {
	x *= n;
	y *= n;
	return *this;
}
Point Point::operator/=(const int n) {
	x /= n;
	y /= n;
	return *this;
}
Point Point::operator=(const Point o) {
	x = o.x;
	y = o.y;
	return *this;
}
bool Point::operator==(const Point o) const {
	return x == o.x && y == o.y;
}
Point::operator Pointf() const {
	return Pointf((float) x, (float) y);
}
Point::operator Rect() const {
	return Rect(x, y, 1, 1);
}
Point::operator Rectf() const {
	return Rectf((float) x, (float) y, 1, 1);
}

Pointf Pointf::operator+(const Pointf o) const {
	return Pointf(x + o.x, y + o.y);
}
Pointf Pointf::operator-(const Pointf o) const {
	return Pointf(x - o.x, y - o.y);
}
Pointf Pointf::operator*(const float n) const {
	return Pointf(x * n, y * n);
}
Pointf Pointf::operator/(const float n) const {
	return Pointf(x / n, y / n);
}
Pointf Pointf::operator+=(const Pointf o) {
	x += o.x;
	y += o.y;
	return *this;
}
Pointf Pointf::operator-=(const Pointf o) {
	x -= o.x;
	y -= o.y;
	return *this;
}
Pointf Pointf::operator*=(const float n) {
	x *= n;
	y *= n;
	return *this;
}
Pointf Pointf::operator/=(const float n) {
	x /= n;
	y /= n;
	return *this;
}
Pointf Pointf::operator=(const Pointf o) {
	x = o.x;
	y = o.y;
	return *this;
}
bool Pointf::operator==(const Pointf o) const {
	return x == o.x && y == o.y;
}
Pointf::operator Point() const {
	return Point((int) x, (int) y);
}
Pointf::operator Rect() const {
	return Rect((int) x, (int) y, 1, 1);
}
Pointf::operator Rectf() const {
	return Rectf(x, y, 1, 1);
}

Rect Rect::operator&(const Rect o) const {
	Rect t = (*this).abs(), s = o.abs();
	int xx = 0, yy = 0, ww = 0, hh = 0;
	if(t.x <= s.rs() && t.rs() > s.x) {
		xx = (int) std::fmax(t.x, s.x);
		ww = (int) std::fmin(	std::fmin(t.w, s.w),
								std::fmin(std::abs(s.rs() - t.x), std::abs(t.rs() - s.x)));
	}

	if(t.y <= s.bot() && t.bot() > s.y) {
		yy = (int) std::fmax(t.y, s.y);
		hh = (int) std::fmin(	std::fmin(t.h, s.h),
								std::fmin(std::abs(s.bot() - t.y), std::abs(t.bot() - s.y)));
	}
	return Rect(xx, yy, ww, hh);
}
Rect Rect::operator|(const Rect o) const {
	Rect t = (*this).abs(), s = o.abs();
	int xx = (int) std::fmin(t.x, s.x), yy = (int) std::fmin(t.y, s.y);
	return Rect(xx, yy, (int) std::fmax(t.x + t.w - xx, s.x + s.w - xx), (int) std::fmax(t.y + t.h - yy, s.y + s.h - yy));
}
Rect Rect::operator>>(const Rect o) const {
	return Rect(o.x, o.y, w, h);
}
Rect Rect::operator<<(const Rect o) const {
	return Rect(x, y, o.w, o.h);
}
Rect Rect::operator>>=(const Rect o) {
	x = o.x;
	y = o.y;
	return *this;
}
Rect Rect::operator<<=(const Rect o) {
	w = o.w;
	h = o.h;
	return *this;
}
Rect Rect::operator=(const Rect o) {
	x = o.x;
	y = o.y;
	w = o.w;
	h = o.h;
	return *this;
}
bool Rect::operator==(const Rect o) const {
	return x == o.x && y == o.y && w == o.w && h == o.h;
}
Rect::operator Rectf() const {
	return Rectf((float) x, (float) y, (float) w, (float) h);
}
Rect::operator Point() const {
	return Point(x, y);
}
Rect::operator Pointf() const {
	return Pointf((float) x, (float) y);
}

Rectf Rectf::operator&(const Rectf o) const {
	Rect t = (*this).abs(), s = o.abs();
	float xx = 0, yy = 0, ww = 0, hh = 0;
	if(t.x <= s.rs() && t.rs() > s.x) {
		xx = (float) std::fmax(t.x, s.x);
		ww = (float) std::fmin(	std::fmin(t.w, s.w),
								std::fmin(std::abs(s.rs() - t.x), std::abs(t.rs() - s.x)));
	}

	if(t.y <= s.bot() && t.bot() > s.y) {
		yy = (float) std::fmax(t.y, s.y);
		hh = (float) std::fmin(	std::fmin(t.h, s.h),
								std::fmin(std::abs(s.bot() - t.y), std::abs(t.bot() - s.y)));
	}
	return Rectf(xx, yy, ww, hh);
}
Rectf Rectf::operator|(const Rectf o) const {
	Rect t = (*this).abs(), s = o.abs();
	float xx = (float) std::fmin(t.x, s.x), yy = (float) std::fmin(t.y, s.y);
	return Rectf(xx, yy, std::fmax(t.x + t.w - xx, s.x + s.w - xx), std::fmax(t.y + t.h - yy, s.y + s.h - yy));
}
Rectf Rectf::operator>>(const Rectf o) const {
	return Rectf(o.x, o.y, w, h);
}
Rectf Rectf::operator<<(const Rectf o) const {
	return Rectf(x, y, o.w, o.h);
}
Rectf Rectf::operator>>=(const Rectf o) {
	x = o.x;
	y = o.y;
	return *this;
}
Rectf Rectf::operator<<=(const Rectf o) {
	w = o.w;
	h = o.h;
	return *this;
}
Rectf Rectf::operator=(const Rectf o) {
	x = o.x;
	y = o.y;
	w = o.w;
	h = o.h;
	return *this;
}
bool Rectf::operator==(const Rectf o) const {
	return x == o.x && y == o.y && w == o.w && h == o.h;
}
Rectf::operator Rect() const {
	return Rect((int) x, (int) y, (int) w, (int) h);
}
Rectf::operator Point() const {
	return Point((int) x, (int) y);
}
Rectf::operator Pointf() const {
	return Pointf(x, y);
}

std::map<char, unsigned int> FormatString::_color_map;
std::map<char, Font*> FormatString::_font_map;

FormatString::FormatString(std::string raw) : _raw(raw) {
    std::function<void(const unsigned int, const unsigned int)> next;
    (next = [&next, this] (const unsigned int start, const unsigned int iteration) {
        FormatString::_Piece piece;

        bool escape = false, color = false, font = false;
        unsigned int i = start, delay = 0;

        for (i; i < _raw.length(); i++) {
            //Font and color can be set if no text has been collected yet
            if (color) {
                auto found = _color_map.find(_raw[i]);
                piece.color = (found != _color_map.end() ? found->second : 0x000000);
                color = false;
                continue;
            }
            if (font) {
                auto found = _font_map.find(_raw[i]);
                piece.font = (found != _font_map.end() ? found->second : Font::get());
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
            case '\\':
                escape = true; 
                break;
            case FormatString::SYM::VAR: /* skip var char */ break;
            case FormatString::SYM::WAIT:
                if (piece.text.length() == 0) {
                    piece.delay++;
                } else {
                    goto out;
                }
                break;
            case FormatString::SYM::COLOR:
                if (piece.text.length() == 0) {
                    color = true;
                } else {
                    goto out;
                }
                break;
            case FormatString::SYM::FONT:
                if (piece.text.length() == 0) {
                    font = true;
                } else {
                    goto out;
                }
                break;
            default: //Regular characters
                _text += _raw[i];
                piece.text += _raw[i];
            }
        }
    out:
        if (i != _raw.length()) {
            next(i, iteration + 1);
        } else {
            _pieces = new FormatString::_Piece[iteration + 1];
        }
        
        _pieces[iteration] = piece;
    })(0, 0);
}

void FormatString::draw() const {
    //DRAW!!
}

FormatString FormatString::operator<<(const int v) const {
    auto i = _raw.find_first_of(SYM::VAR);
    if(i == std::string::npos) {
        return *this;
    } else {
        return FormatString(_raw.substr(0, i) + std::to_string(v) + _raw.substr(i + 1));
    }
}

FormatString FormatString::operator<<(const std::string v) const {
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
            file >> s >> v;
            add_color(s, v);
        } else if(t == 'f') {
            std::string v;
            file >> s >> v;
            add_font(s, Font::get(v));
        }
    }
}