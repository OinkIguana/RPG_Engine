#pragma once

#include <map>
#include <string>
#include <fstream>
#include <functional>
#include "types.h"
#include "image.h"

class Sprite {
public:
    // Get the sprite with the requested name, or create one which has the image given
    static Sprite* get(const std::string& name, Image* image = NULL);
    ~Sprite();
    
    // Split the entire image into base shaped frames
    void set_frames(const Rect& base);
    // Split the requested part of the image into base shaped frames
    void set_frames(const Rect& base, const Rect& part);
    // Split the entire image into base shaped frames separated by the given amount
    void set_frames(const Rect& base, const Point& sep);
    // Split the requested part  of the image into base shaped frames separated by the given amount
    void set_frames(const Rect& base, const Rect& part, const Point& sep);
    // Split the image into the given list of frames
    void set_frames(const unsigned int& count, Rect* frames);

    // Get the Rect corresponding to the given frame
    inline Rect frame(const unsigned int& i) const { return _frames[i]; }
    // Get the number of frames
    inline unsigned int frames() const { return _frame_count; }

    // Draw the frame to the screen at pos
    void draw(const Point& pos, const unsigned int& frame);

    /* Import sprites from a file of the form
    *  =============
    *  sprite_name image_name
    *  f x y w h                # base rect
    *  b x y w h                # bounds rect
    *  s x y                    # separation
    *  x                        # delimeter
    *  sprite_name2 image_name2
    *  n 2                      # number of frames
    *  x1 y1 w1 h1
    *  x2 y2 w2 h2  
    */
    static void import(const std::string& path);
private:
    // Create a sprite with the given image
    Sprite(const std::string& name, Image* img);

    const std::string _name;
    const Point _origin;
    Image* _image;
    Rect* _frames;
    unsigned int _frame_count = 1;

    static std::map<std::string, Sprite*> all_sprites;
};