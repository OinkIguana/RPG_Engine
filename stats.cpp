#include "stats.h"
std::map<std::string, Stat*> Stat::all_stats = std::map<std::string, Stat*> ();

StatList::StatList(std::string str) {
    read(str);
}

Stat* Stat::get(std::string name, std::string desc) {
    auto old = all_stats.find(name);
    if(old != all_stats.end()) {
        return old->second;
	} else {
        all_stats[name] = new Stat(name, desc);
        return all_stats[name];
	}
}

std::string Stat::toString(const int l) const {
	auto i = _desc.find_first_of('`');
	return i == std::string::npos ? (_desc == "" ? _name + ": " + std::to_string(l) : _desc) : _desc.substr(0, i) + std::to_string(l) + _desc.substr(i + 1);
}

void Stat::import(const std::string fname) {
    std::ifstream file(fname);
    do {
        std::string name, desc;
        std::getline(file, name, ':');
        std::getline(file, desc);
        Stat::get(name, desc);
    } while (!file.eof());
}

StatList StatList::operator+(const StatList o) const {
	StatList both;
	for (auto i = _stats.begin(); i != _stats.end(); ++i) {
		both[i->first] = i->second;
	}
	for (auto i = o._stats.begin(); i != o._stats.end(); ++i) {
		both[i->first] += i->second;
	}
	return both;
}

StatList StatList::operator-(const StatList o) const {
	StatList both;
	for (auto i = _stats.begin(); i != _stats.end(); ++i) {
		both[i->first] = i->second;
	}
	for (auto i = o._stats.begin(); i != o._stats.end(); ++i) {
		both[i->first] -= i->second;
	}
	return both;
}

StatList StatList::operator+=(const StatList o) {
	for (auto i = o._stats.begin(); i != o._stats.end(); ++i) {
		(*this)[i->first] += i->second;
	}
	return *this;
}

StatList StatList::operator-=(const StatList o) {
	for (auto i = o._stats.begin(); i != o._stats.end(); ++i) {
		(*this)[i->first] -= i->second;
	}
	return *this;
}

int& StatList::operator[](Stat* i) {
	auto old = _stats.find(i);
	if (old == _stats.end()) {
		_stats[i] = 0;
		return _stats[i];
	}
	else {
		return old->second;
	}
}

bool StatList::read(std::string list) {
    int colon, comma;
    do {
        colon = list.find(':');
        if (colon == std::string::npos) {
            return false;
        }
        comma = list.find(',');
        try {
            _stats[Stat::get(list.substr(0, colon))] = std::stoi(list.substr(colon + 1, comma - 1));
        } catch(std::invalid_argument) {
            return false;
        }
        list = list.substr(comma + 1);
    } while (comma != std::string::npos);
    return true;
}

StatList::operator std::string() const {
	std::string str;
	for (auto i = stats.begin(); i != stats.end(); i++) {
		str += i->first->toString(i->second);
		str += '\n';
	}
	return str;
}

std::ostream& operator<<(std::ostream& o, const StatList& s) {
	o << (std::string) s;
	return o;
}