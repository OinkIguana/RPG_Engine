#pragma once

#include <map>
#include <string>
#include <functional>
#include <cstdarg>

// An objective along a Storyline
class Quest {
public:
    // A quest returned when there is no quest
    static Quest nullquest;
    enum State { NOT_STARTED, STARTED, FINISHED };

    // Create a new quest. Strings are actually arbitrary. Use as you wish. Quest equality is based on title
    // check should return a bool, whether the conditions are satisfied or not
    // finish is called once, after check returns true. Use it to provide rewards, set flags, trigger events, etc.
    // Both functions are passed the current quest as a parameter
    // Use quest.flags() if necessary to set/check flags
    Quest() {}
    Quest(  std::function<bool(Quest*)> check, std::function<void(Quest*)> finish,
            const std::string& title = "", const std::string& description = "", const std::string& goal = "", const std::string& reward = "") :
            _check(check), _finish(finish), _title(title), _description(description), _goal(goal), _reward(reward) {}
    inline ~Quest() {}

    inline std::string title() const { return _title; }
    inline std::string description() const { return _description; }
    inline std::string goal() const { return _goal; }
    inline std::string reward() const { return _reward; }

    inline State state() const { return _state; }
    inline bool started() const { return _state == STARTED; }
    inline bool finished() const { return _state == FINISHED; }

    inline void start() { _state = STARTED; }
    inline bool check() { return (_state == STARTED) ? _check(this) : false; }
    inline void finish() { _state = FINISHED; _finish(this); }

    inline unsigned int flags() const { return _flags; }
    inline unsigned int flags(const unsigned int& flags) { return _flags = flags; }

    inline bool operator==(const Quest& o) const { return _title == o._title; }
private:
    std::string _title;
    std::string _description;
    std::string _goal;
    std::string _reward;
    unsigned int _flags = 0b00000000;
    State _state = NOT_STARTED;
    std::function<bool(Quest*)> _check = [] (Quest*) { return false; };
    std::function<void(Quest*)> _finish = [] (Quest*) {};
};

// A series of Quests to tell a story
class Storyline {
public:
    Storyline(const std::string& _name, const unsigned int length, ...);
    inline ~Storyline() { delete[] _quests; }

    inline std::string name() const { return _name; }

    inline unsigned int length() const { return _length; }
    inline unsigned int progress() const { return _progress; }
    inline Quest& current_quest() const { return _progress < _length ? _quests[_progress] : Quest::nullquest; }
    inline Quest& quest(const unsigned int& i) { return _quests[i]; }

    inline bool check() { return current_quest().check(); }
    inline void make_progress() { current_quest().finish(); _progress++; }
private:
    std::string _name;
    Quest* _quests;
    unsigned int _length;
    unsigned int _progress = 0;
};

// Holds and manages multiple Storylines
class Progress {
public:
    static void check();
    inline static void add_storyline(Storyline* which) { all_storylines[which->name()] = which; }
    inline static void remove_storyline(std::string name) { delete all_storylines[name]; all_storylines.erase(name); }
private:
    static std::map<std::string, Storyline*> all_storylines;
};