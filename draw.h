#pragma once

#include <SDL.h>
#include "types.h"

class draw {
public:
    // Draw an entire texture stretched to fill a given space
    static void texture(const Rect& p, const int& depth, SDL_Texture* tex);
    // Draw an entire texture at the given point
    static void texture(const Point& p, const int& depth, SDL_Texture* tex);
    // Draw part of the texture at the given point
    static void texture_part(const Point& p, const int& depth, SDL_Texture* tex, const Rect& src);
    // Draw a surface at the given point
    static void surface(const Point& p, const int& depth, SDL_Surface* surf);
    // Clear the screen
    static void clear();
    // Present the image to the screen
    static void render();

    // Draw a rectangle
    static void rect(const Rect& rect, const int& depth = 0);

    // Set the color for various things
    static void set_color(const Color&);
private:
    struct Carry {
        friend class draw;

        Carry(Carry* parent = nullptr) : _parent(parent) {}
        ~Carry() { if (_temp) SDL_DestroyTexture(_tex); }
        // Pick up a new instance
        Carry* operator()(const Rect&, const int&, const Rect& piece, SDL_Texture*, const bool& temp = false);
        // Compare depth
        inline bool operator<(const Carry& o) { return _depth < o._depth; }
        // Get the next instance in the list
        void extract(Carry** list);
        // Extract all instances and put them into an array, sorted by depth
        static Carry** extract_all(Carry* first, unsigned int& size);
    private:
        Carry* _parent = nullptr;
        int _depth = 0;
        Rect _pos;
        Rect _piece;
        SDL_Texture* _tex = NULL;
        bool _temp;

        static int _size;
    };
    static Carry* _carry;
    static Color _color;
};