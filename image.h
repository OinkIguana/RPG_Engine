#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sdl.h>
#include <SDL_image.h>
#include "draw.h"
#include "types.h"

class Image {
public:
    // Get the image with the given name, or add one from a url
    static Image* get(const std::string& name, const std::string& url = "");
    ~Image();

    // Draw part of the image to the screen
    void draw(const Point& pos, const Rect& src) const;
    // Draw the whole image to the screen
    void draw(const Point& pos) const;

    // Get the width of the image
    inline unsigned int width() const { return _width; };
    // Get the height of the image
    inline unsigned int height() const { return _height; };

    /* Import images from a file in the form of:
    *  ============
    *  image_name "path/to/file.png"
    *  image_name "path/to/file2.png"
    *  ============
    */
    static void import(const std::string& path);
private:
    // Load a new image from a file
    Image(const std::string& name, const std::string& file);
    const std::string _name;
    const std::string _file;
    SDL_Texture* _tex;
    unsigned int _width;
    unsigned int _height;
    static std::map<std::string, Image*> all_images;
};