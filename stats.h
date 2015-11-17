#pragma once

#include <map>
#include <string>
#include <fstream>
#include "formatstring.h"

class Stat {
public:
    /*
        Gets the pointer to the Stat with the given name. If the Stat has not yet been used, it sets the description
    */
    static Stat* get(std::string, std::string = "");
    ~Stat() { all_stats.erase(_name); }

    std::string to_string(const int) const;
    
    static void import(const std::string);
    inline static void delete_all() { all_stats.clear(); }
private:
    /*
        Use Stat::get to create/use Stats
    */
    Stat(const std::string name, const std::string desc) : _name(name), _desc(desc) {};

    const std::string _name;
    const FormatString _desc;

    static std::map<std::string, Stat*> all_stats;
};

class StatList {
public:
    StatList() {}
    StatList(std::string);
    ~StatList() {}

    StatList operator+(const StatList) const;
    StatList operator-(const StatList) const;
    StatList operator+=(const StatList);
    StatList operator-=(const StatList);
    int& operator[](Stat*);

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream&, const StatList&);

    bool read(std::string);
private:
    std::map<Stat*, int> _stats;
};