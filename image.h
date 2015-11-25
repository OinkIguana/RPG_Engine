#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sdl.h>
#include <SDL_image.h>
#include "draw.h"
#include "types.h"

class Tile;

// An Image, for both Sprites and Tiles
class Image {
public:
    // Get the image with the given name, or add one from a url
    static Image* get(const std::string& name, const std::string& url = "");
    // Create a named image from a list of tiles
    static Image* compose(const std::string& name, const unsigned int& n, Tile** tiles);
    // Create an unnamed image from a list of tiles
    static Image* compose(const unsigned int& n, Tile** tiles);
    ~Image();

    // Draw part of the image to the screen
    void draw(const Point& pos, const Rect& src, const int& depth = 0) const;
    // Draw part of the image to the screen, stretched to fill a space
    void draw(const Rect& pos, const Rect& src, const int& depth = 0) const;
    // Draw the whole image to the screen
    void draw(const Point& pos, const int& depth = 0) const;
    // Draw the whole image to the screen, stretched to fill a space
    void draw(const Rect& pos, const int& depth = 0) const;

    inline std::string name() const { return _name; }
    // Get the width of the image
    inline unsigned int width() const { return _width; };
    // Get the height of the image
    inline unsigned int height() const { return _height; };

    // Copy a portion of the image to another surface
    void Image::copy_to_surface(SDL_Surface* surf, SDL_Rect& piece, SDL_Rect& pos) const;

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
    // Load a new image by building it from parts of other images
    Image(const std::string& name, const unsigned int& n, Tile** tiles);
    const std::string _name;
    const std::string _file;
    SDL_Texture* _tex;
    SDL_Surface* _surf;
    unsigned int _width;
    unsigned int _height;
    static std::map<std::string, Image*> all_images;
};