#ifndef __RPG_TYPES_H__
#define __RPG_TYPES_H__

#include <cmath>
#include <string>
#include <map>
#include <functional>
#include <fstream>
#include "font.h"

struct Point;
struct Pointf;
struct Rect;
struct Rectf;
class FormatString;

// Constants for directions
enum { LEFT, RIGHT, UP, DOWN };

// A point, consisting of a position (x and y)
struct Point {
	int x, y;

	Point(const int a = 0, const int b = 0) : x(a), y(b) {}
	~Point() {}

	// Returns the distance from this point to another given point
	inline float distance(const Point o) const { return (float)std::sqrt(std::pow(x - o.x, 2) + std::pow(y - o.y, 2)); }

	Point operator+(const Point) const;
	Point operator-(const Point) const;
	Point operator*(const int) const;
	Point operator/(const int) const;
	Point operator+=(const Point);
	Point operator-=(const Point);
	Point operator*=(const int);
	Point operator/=(const int);
	Point operator=(const Point);

	bool operator==(const Point) const;

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
	Pointf operator*(const float) const;
	Pointf operator/(const float) const;
	Pointf operator+=(const Pointf);
	Pointf operator-=(const Pointf);
	Pointf operator*=(const float);
	Pointf operator/=(const float);
	Pointf operator=(const Pointf);

	bool operator==(const Pointf) const;

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

	// Returns the area of the rectangle
	inline int area() const { return w * h; }

	// Returns the right side x position of the rectangle
	inline int rs() const { return x + w; }

	// Returns the bottom side y position of the rectangle
	inline int bot() const { return y + h; }

	// Returns an equivalent rectangle with all values positive
	inline Rect abs() const { return Rect((int) std::fmin(x + w, x), (int) std::fmin(y + h, y), (int) std::abs(w), (int) std::abs(h)); }

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

	// Resizes the current rectangle to the given rectangle's size
	Rect operator<<=(const Rect);

    Rect operator=(const Rect);
	bool operator==(const Rect) const;

	operator Rectf() const;
	operator Point() const;
	operator Pointf() const;
};

// A higher precision rectangle, consisting of a position and a width/height.
struct Rectf {
	float x, y, w, h;

	Rectf(const float a = 0, const float b = 0, const float c = 0, const float d = 0) : x(a), y(b), w(c), h(d) {}
	Rectf(const Pointf a, const Pointf b) : x(a.x), y(a.y), w(b.x - a.x), h(b.y - a.y) {}

	// Returns the area of the Rect
	inline float area() const { return w * h; }

	// Returns the right side x position of the rectangle
	inline float rs() const { return x + w; }

	// Returns the bottom side y position of the rectangle
	inline float bot() const { return y + h; }

	// Returns an equivalent rectangle with all values positive
	inline Rectf abs() const { return Rectf(std::fmin(x + w, x), std::fmin(y + h, y), std::abs(w), std::abs(h)); }

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

	Rectf operator=(const Rectf);
	bool operator==(const Rectf) const;

	operator Rect() const;
	operator Point() const;
	operator Pointf() const;
};

// A string that can be drawn formatted with colours, fonts, variables, etc
class FormatString {
public:
    FormatString(std::string);
    ~FormatString() {}

    //Draw the string (formatted) to the screen
    void draw() const;

    //Get the text only part of the string
    inline operator std::string() const { return _text; }
    inline std::string to_string() const { return _text; }

    //Replace the first SYM::VAR with the given value
    FormatString operator<<(const int) const;
    FormatString operator<<(const std::string) const;

    //Compare two FormatStrings, based on their raw strings
    inline bool operator==(const FormatString& o) const { return _raw == o._raw; }
    //Compare a String to a FormatString (based on the _raw string)
    inline bool operator==(const std::string& o) const { return _raw == o; }

    //Special character symbols for the formatting
    const enum SYM {
        VAR = '%',
        COLOR = '#',
        FONT = '$',
        WAIT = '`'
    };

    //Add a color to the valid characters to come after SYM::COLOR
    inline static void add_color(const char key, unsigned const int value) { _color_map[key] = value; }
    //Add a font to the valid characters to come after SYM::FONT
    inline static void add_font(const char key, Font* value) { _font_map[key] = value; }
    /*
        Import many colors/fonts from a file, in the form of:
        c k 0x000000
        f a Arial
    */
    static void import(const std::string);
private:
    std::string _raw;
    std::string _text;

    typedef struct {
        std::string text = "";
        unsigned int delay = 0;
        unsigned int color = 0;
        Font* font = Font::get();
    } _Piece;
    _Piece * _pieces;
    unsigned int _length;

    static std::map<char, unsigned int> _color_map;
    static std::map<char, Font*> _font_map;
};

inline FormatString operator""_format(const char* str, size_t) { return FormatString(str); }

#endif