#include "stats.h"

std::map<std::string, Stat*> Stat::all_stats = std::map<std::string, Stat*> ();

Stat::Stat(std::string a, std::string b) : name(a), desc(b) {
	auto existingStat = all_stats.find(name);
	if (existingStat != all_stats.end()){
		throw existingStat->second;
	} else {
		all_stats[name] = this;
	}
}
Stat* Stat::get(std::string name, std::string desc) {
	try {
		return new Stat(name, desc);
	} catch (Stat* old) {
		return old;
	}
}
std::string Stat::operator|(const int l) const {
	auto i = desc.find_first_of('`');
	return i == std::string::npos ? desc : desc.substr(0, i) + std::to_string(l) + desc.substr(i + 1);
}

StatList StatList::operator+(const StatList o) const {
	StatList both;
	for (auto i = stats.begin(); i != stats.end(); ++i) {
		both[i->first] = i->second;
	}
	for (auto i = o.stats.begin(); i != o.stats.end(); ++i) {
		both[i->first] += i->second;
	}
	return both;
}
StatList StatList::operator-(const StatList o) const {
	StatList both;
	for (auto i = stats.begin(); i != stats.end(); ++i) {
		both[i->first] = i->second;
	}
	for (auto i = o.stats.begin(); i != o.stats.end(); ++i) {
		both[i->first] -= i->second;
	}
	return both;
}
StatList StatList::operator+=(const StatList o) {
	for (auto i = o.stats.begin(); i != o.stats.end(); ++i) {
		(*this)[i->first] += i->second;
	}
	return *this;
}
StatList StatList::operator-=(const StatList o) {
	for (auto i = o.stats.begin(); i != o.stats.end(); ++i) {
		(*this)[i->first] -= i->second;
	}
	return *this;
}
int& StatList::operator[](Stat* i) {
	auto old = stats.find(i);
	if (old == stats.end()) {
		stats[i] = 0;
		return stats[i];
	}
	else {
		return old->second;
	}
}
StatList::operator std::string() const {
	std::string str;
	for (auto i = stats.begin(); i != stats.end(); i++) {
		str += *(i->first) | i->second;
		str += '\n';
	}
	return str;
}
std::ostream& operator<<(std::ostream& o, const StatList& s) {
	o << (std::string) s;
	return o;
}