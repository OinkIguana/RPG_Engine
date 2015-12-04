#pragma once

#include <map>
#include <string>
#include <fstream>
#include "formatstring.h"

// A stat
class Stat {
public:
    /*
        Gets the pointer to the Stat with the given name. If the Stat has not yet been used, it sets the description
    */
    static Stat* get(std::string, std::string = "");
    inline ~Stat() { all_stats.erase(_name); }

    // Inserts the given amount into the stat description, and produces the string of Name: Description
    std::string to_string(const int amount) const;
    // Produces the string of Name: Description
    std::string to_string() const;
    
    /* Import stats from a file of the form:
    *  Name:Desc
    *  Name:Desc With % Inserted Value
    */
    static void import(const std::string);
private:
    /*
        Use Stat::get to create/use Stats
    */
    Stat(const std::string name, const std::string desc) : _name(name), _desc(desc) {};

    const std::string _name;
    const FormatString _desc;

    static std::map<std::string, Stat*> all_stats;
};

// A set of stats with levels
class StatList {
public:
    StatList() {}
    StatList(std::string);
    ~StatList() {}

    // Add two stat lists
    StatList operator+(const StatList) const;
    // Subtract a second stat list from the first
    StatList operator-(const StatList) const;
    StatList operator+=(const StatList);
    StatList operator-=(const StatList);
    int& operator[](Stat*);

    // Turn a stat list to a string representation
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream&, const StatList&);

    // Produce a stat list based on a string representation: stat:level,stat2:level2
    bool read(std::string list);
private:
    std::map<Stat*, int> _stats;
};