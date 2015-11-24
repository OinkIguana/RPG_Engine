#pragma once

#include <map>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>
#include "font.h"
#include "config.h"

// A string that can be drawn formatted with colours, fonts, variables, etc
class FormatString {
public:
    FormatString(const std::string&, const int& = -1);
    ~FormatString();

    //Draw the string (formatted) to the screen
    void draw(const Point& pos);

    //Get the text only part of the string
    inline operator std::string() const { return _text; }
    inline std::string to_string() const { return _text; }

    //Get calculated width of the string
    inline int width() const { return _width; }
    //Get calculated height of the string
    inline int height() const { return _height; }
    //Get the length of the string (including wait times)
    inline unsigned int length() const { return _text.length() + _total_wait; }

    //Get a piece of the FormatString
    FormatString upto(const unsigned int& count = std::string::npos) const;

    //Merge two FormatStrings
    inline FormatString operator+(const FormatString& o) const { return FormatString(_raw + o._raw); }

    //Replace the first SYM::VAR with the given value
    FormatString operator<<(const int& v) const;
    //Replace the first SYM::VAR with the given value
    FormatString operator<<(const std::string& v) const;

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
    /* Import many colors/fonts from a file, in the form of:
    *  ==============
    *  c k 0x000000
    *  f a arial
    *  ==============
    */
    static void import(const std::string);
private:
    std::string _raw;
    std::string _text;

    unsigned int _width;
    unsigned int _height = 0;
    unsigned int _total_wait = 0;

    SDL_Texture* _tex = NULL;

    typedef struct {
        std::string text = "";
        unsigned int delay = 0;
        unsigned int color = 0;
        Font* font = Font::get();
        unsigned int x = 0;
        unsigned int y = 0;
    } _Piece;
    _Piece * _pieces;
    unsigned int _length;

    static std::map<char, unsigned int> _color_map;
    static std::map<char, Font*> _font_map;
};

inline FormatString operator""_format(const char* str, size_t) { return FormatString(str); }