#pragma once

#include <sdl.h>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <cstdarg>
#include <iostream>

struct Point;
struct Pointf;
struct Rect;
struct Rectf;

// A representation of an angle
struct Angle {
    int dx, dy;
    int deg;
    double rad;
    Angle(const Point& p);
    Angle(const int& dx, const int& dy);
    Angle(const int& deg);
    Angle(const double& rad);

    Angle operator+(const Angle& o) const;
    Angle operator-(const Angle& o) const;
    Angle operator-() const;
    Angle operator+=(const Angle& o);
    Angle operator-=(const Angle& o);

    // Compares angles (at degree level of accuracy)
    bool operator==(const Angle& o) const;
    bool operator!=(const Angle& o) const;
};

Angle operator ""_deg(unsigned long long);

// Constants for directions
enum { LEFT, RIGHT, UP, DOWN };

// A point, consisting of a position (x and y)
struct Point {
    int x, y;

    Point(const int a = 0, const int b = 0) : x(a), y(b) {}
    ~Point() {}

    // Returns the distance from this point to another
    inline float distance(const Point o) const { return (float)std::sqrt(std::pow(x - o.x, 2) + std::pow(y - o.y, 2)); }

    Point operator+(const Point) const;
    Point operator-(const Point) const;
    Point operator-() const;
    Point operator*(const int) const;
    Point operator/(const int) const;
    Point operator+=(const Point);
    Point operator-=(const Point);
    Point operator*=(const int);
    Point operator/=(const int);
    Point operator=(const Point);

    bool operator==(const Point) const;
    bool operator!=(const Point) const;

    operator SDL_Point() const;
    operator Pointf() const;
    operator Rect() const;
    operator Rectf() const;
};

// A higher precision point, consisting of a position (x and y)
struct Pointf{
    float x, y;

    Pointf(const float a = 0, const float b = 0) : x(a), y(b) {}
    ~Pointf() {}

     // Returns the distance from this point to another given point
    inline float distance(const Pointf o) const { return std::sqrt(std::pow(x - o.x, 2) + std::pow(y - o.y, 2)); }

    Pointf operator+(const Pointf) const;
    Pointf operator-(const Pointf) const;
    Pointf operator-() const;
    Pointf operator*(const float) const;
    Pointf operator/(const float) const;
    Pointf operator+=(const Pointf);
    Pointf operator-=(const Pointf);
    Pointf operator*=(const float);
    Pointf operator/=(const float);
    Pointf operator=(const Pointf);

    bool operator==(const Pointf) const;
    bool operator!=(const Pointf) const;

    operator SDL_Point() const;
    operator Point() const;
    operator Rect() const;
    operator Rectf() const;
};

/*
    A rectangle, consisting of a position and a width/height.
*/
struct Rect {
    int x, y, w, h;

    Rect(const int a = 0, const int b = 0, const int c = 0, const int d = 0) : x(a), y(b), w(c), h(d) {}
    Rect(const Point a, const Point b) : x(a.x), y(a.y), w(b.x - a.x), h(b.y - a.y) {}
    static const Rect no_box;

    // Returns the area of the rectangle
    inline int area() const { return w * h; }

    // Returns the right side x position of the rectangle
    inline int rs() const { return x + w; }

    // Returns the bottom side y position of the rectangle
    inline int bot() const { return y + h; }

    // Returns an equivalent rectangle with all values positive
    inline Rect abs() const { return Rect((int) std::fmin(x + w, x), (int) std::fmin(y + h, y), (int) std::abs(w), (int) std::abs(h)); }

    // Determines if two rectangles lie against each other
    inline bool against(const Rect& o) const {
        return (((rs() == o.x) || (x == o.rs())) && (bot() > o.y && y < o.bot())) ||
               (((bot() == o.y) || (y == o.bot())) && (rs() > o.x && x < o.rs()));   
    }

    // Determines if this rectangle contains another
    inline bool contains(const Rect& o) const { return ((*this) | o) == (*this); }

    // Calculates a rectangle representing the intersection of two rectangles
    Rect operator&(const Rect) const;

    // Calculates a rectangle which contains both given rectangles
    Rect operator|(const Rect) const;

    // Returns a rectangle equivalent to moving the current rectangle to the given one's position
    Rect operator>>(const Rect) const;

    // Returns a rectangle equivalent to moving the given rectangle to the current one's position
    Rect operator<<(const Rect) const;

    // Moves the current rectangle to the given rectangle's position
    Rect operator>>=(const Rect);

    // Moves the current rectangle by the given distance
    Rect operator+(const Point) const;

    // Resizes the current rectangle to the given rectangle's size
    Rect operator<<=(const Rect);

    Rect operator=(const Rect);
    bool operator==(const Rect) const;
    bool operator!=(const Rect) const;

    operator SDL_Rect() const;
    operator Rectf() const;
    operator Point() const;
    operator Pointf() const;
};

// A higher precision rectangle, consisting of a position and a width/height.
struct Rectf {
    float x, y, w, h;

    Rectf(const float a = 0, const float b = 0, const float c = 0, const float d = 0) : x(a), y(b), w(c), h(d) {}
    Rectf(const Pointf a, const Pointf b) : x(a.x), y(a.y), w(b.x - a.x), h(b.y - a.y) {}
    static const Rectf no_box;

    // Returns the area of the Rect
    inline float area() const { return w * h; }

    // Returns the right side x position of the rectangle
    inline float rs() const { return x + w; }

    // Returns the bottom side y position of the rectangle
    inline float bot() const { return y + h; }

    // Returns an equivalent rectangle with all values positive
    inline Rectf abs() const { return Rectf(std::fmin(x + w, x), std::fmin(y + h, y), std::abs(w), std::abs(h)); }

    // Determines if two rectangles lie against each other
    inline bool against(const Rectf& o) const {
        return (((rs() == o.x) || (x == o.rs())) && (bot() > o.y && y < o.bot())) ||
                (((bot() == o.y) || (y == o.bot())) && (rs() > o.x && x < o.rs()));
    }

    // Determines if this rectangle contains another
    inline bool contains(const Rectf& o) const { return ((*this) | o) == (*this); }

    // Calculates a rectangle representing the intersection of two rectangles
    Rectf operator&(const Rectf) const;

    // Calculates a rectangle which contains both given rectangles
    Rectf operator|(const Rectf) const;

    // Returns a rectangle equivalent to moving the current rectangle to the given one's position
    Rectf operator>>(const Rectf) const;

    // Returns a rectangle equivalent to moving the given rectangle to the current one's position
    Rectf operator<<(const Rectf) const;

    // Moves the current rectangle to the given rectangle's position
    Rectf operator>>=(const Rectf);

    // Resizes the current rectangle to the given rectangle's size
    Rectf operator<<=(const Rectf);

    // Moves the current rectangle by the given distance
    Rectf operator+(const Pointf) const;

    Rectf operator=(const Rectf);
    bool operator==(const Rectf) const;
    bool operator!=(const Rectf) const;

    inline operator SDL_Rect() const;
    inline operator Rect() const;
    inline operator Point() const;
    inline operator Pointf() const;
};

// Provides convenient conversion between various color formats
struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a = 0xFF;

    Color(Uint8 rr, Uint8 gg, Uint8 bb, Uint8 aa = 0xFF) : r(rr), g(gg), b(bb), a(aa) {};

    static Color hex(unsigned int);

    inline operator unsigned int() const { return (r << 16) + (g << 8) + b; }
    inline operator SDL_Color() const { return { r, g, b, a }; }
};

template<typename T>
// A sequence of values which can be accessed in one direction
struct Sequence {
    Sequence(const unsigned int len, ...) : _length(len) {
        va_list seq;
        va_start(seq, len);
        _values = new T[len];
        for (unsigned int i = 0; i < len; i++) {
            _values[i] = va_arg(seq, T);
        }
        va_end(seq);
    }
    ~Sequence() { delete[] _values; }

    // Go forward a value
    inline T operator++() { return _values[(_index = (_index + 1) % length()) / _stretch]; }
    // Go back a value
    inline T operator--() { return _values[(_index = (_index - 1 + length()) % length()) / _stretch]; }
    // Change the index
    inline T operator=(const unsigned int& i) { return _values[(_index = i % length()) / _stretch]; }
    
    // Access a value at an index
    inline T operator[](const unsigned int& i) const { return _values[(i % length()) / _stretch]; }

    inline operator T() { return _values[_index / _stretch]; }
    inline unsigned int length() const { return _length * _stretch; }
private:
    T * _values;
    const unsigned int _length;
    unsigned int _index = 0;
    unsigned int _stretch = 1;
};