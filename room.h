#pragma once

#include <map>
#include <string>
#include "rpg.h"

// A base room. Individual rooms should be created using the Room Editor
class Room {
public:
    static Room* get(const std::string& name);
    ~Room();

    inline std::string name() const { return _name; }
    inline unsigned int width() const { return _width; }
    inline unsigned int height() const { return _height; }

    // Add one room to the list of rooms
    template<class T>
    static void add_room();

    // Instantiates the rooms
    static void import();

    // End the current room and start the next
    void go_to();
protected:
    Room(const std::string& name, const int& width, const int& height) : _name(name), _width(width), _height(height){};
    const std::string _name;
    const unsigned int _width;
    const unsigned int _height;

    virtual void tiles() = 0;
    virtual void actors() = 0;
    virtual void on_room_start() {};
    virtual void on_room_end() {};
private:
    void start();
    void end();

    static std::map<std::string, Room*> all_rooms;
    static Room* current_room;
};

template<class T>
inline void Room::add_room() {
    Room* rm = new T();
    all_rooms[rm->name()] = rm;
}