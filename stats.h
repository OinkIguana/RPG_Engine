#ifndef __RPG_STATS_H__
#define __RPG_STATS_H__

#include <string>
#include <map>
#include <iostream>

class Stat {
public:
	/*
		Gets the pointer to the Stat with the given name. If the Stat has not yet been used, it sets the description
	*/
	static Stat* get(std::string, std::string = "");
	~Stat() {}

	std::string operator|(const int) const;
private:
	/*
		Use Stat::get to create/use Stats
	*/
	Stat(std::string, std::string);

	std::string name;
	std::string desc;

	static std::map<std::string, Stat*> all_stats;
};

class StatList {
public:
	StatList() {}
	~StatList() {}

	StatList operator+(const StatList) const;
	StatList operator-(const StatList) const;
	StatList operator+=(const StatList);
	StatList operator-=(const StatList);
	int& operator[](Stat*); 

	operator std::string() const;
	friend std::ostream& operator<<(std::ostream&, const StatList&);
private:
	std::map<Stat*, int> stats;
};

#endif