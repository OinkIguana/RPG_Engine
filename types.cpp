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
Point::operator SDL_Point() const {
    return { x, y };
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
Pointf::operator SDL_Point() const {
    return { (int)x, (int)y };
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
        ww = (int) std::fmin(    std::fmin(t.w, s.w),
                                std::fmin(std::abs(s.rs() - t.x), std::abs(t.rs() - s.x)));
    }

    if(t.y <= s.bot() && t.bot() > s.y) {
        yy = (int) std::fmax(t.y, s.y);
        hh = (int) std::fmin(    std::fmin(t.h, s.h),
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
Rect::operator SDL_Rect() const {
    return { x, y, w, h };
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
        ww = (float) std::fmin(    std::fmin(t.w, s.w),
                                std::fmin(std::abs(s.rs() - t.x), std::abs(t.rs() - s.x)));
    }

    if(t.y <= s.bot() && t.bot() > s.y) {
        yy = (float) std::fmax(t.y, s.y);
        hh = (float) std::fmin(    std::fmin(t.h, s.h),
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
Rectf::operator SDL_Rect() const {
    return { (int)x, (int)y, (int)w, (int)h };
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

Color Color::hex(unsigned int c) {
    Uint8 r, g, b;
    r = (0xFF0000 & c) >> 16;
    g = (0x00FF00 & c) >> 8;
    b = 0x0000FF & c;
    return Color(r, g, b);
}
