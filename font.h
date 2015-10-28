#ifndef __RPG_FONT_H__
#define __RPG_FONT_H__

#include <sdl.h>
#include <fstream>
#include <string>

class Font {
public:
    static Font* get(std::string = "", std::string = "") { return nullptr; }
    ~Font() {}

    static void import(std::string);
private:
    Font() {}

};

#endif