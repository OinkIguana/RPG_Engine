#ifndef __RPG_STATS_H__
#define __RPG_STATS_H__

#include <string>
#include <map>
#include <fstream>

class Stat {
public:
    /*
		Gets the pointer to the Stat with the given name. If the Stat has not yet been used, it sets the description
	*/
	static Stat* get(std::string, std::string = "");
    ~Stat() { all_stats.erase(name); }

	std::string toString(const int) const;

    static void import(const std::string);
private:
    /*
        Use Stat::get to create/use Stats
    */
    Stat(const std::string name, const std::string desc) : _name(name), _desc(desc) {};

	const std::string _name;
	const std::string _desc;

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

	operator std::string() const;
	friend std::ostream& operator<<(std::ostream&, const StatList&);

    bool read(std::string);
private:
    std::map<Stat*, int> _stats;
};

#endif