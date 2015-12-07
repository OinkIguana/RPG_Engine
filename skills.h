#pragma once
#include <fstream>
#include <cstdarg>
#include <string>
#include <map>

class SkillTree;

// A skill
class Skill {
public:
    static Skill* get(const std::string& name);

    inline std::string name() const { return _name; }
    inline std::string desc() const { return _desc; }
    inline unsigned int max_level() const { return _max_level; }

    /* Import skills from a file of the form:
    ==================
    Name
    Desc
    MaxLevel

    Name
    Desc
    MaxLevel
    ==================
    */
    static void import(const std::string& url);
private:
    Skill(const std::string& name, const std::string& description = "", const unsigned int& max_level = 1)
        : _name(name), _desc(description), _max_level(max_level) {}

    std::string _name;
    std::string _desc;
    unsigned int _max_level;

    static std::map<std::string, Skill*> all_skills;
};

// A branch of a skill tree, with a node on each end
class SkillBranch {
    friend std::istream& operator>>(std::istream& file, SkillBranch& branch);
public:
    SkillBranch(const std::string& end = "", const unsigned int& length = 1) : _end(end), _length(length) {}

    inline std::string end() const { return _end; }
    inline unsigned int length() const { return _length; }
private:
    std::string _end = "";
    unsigned int _length;
};

// A node in a skill tree, with many branches
class SkillNode {
    friend std::istream& operator>>(std::istream& file, SkillNode& node);
public:
    SkillNode(const std::string& name = "Base") : _name(name), _prereq_points(0) {};
    SkillNode(const std::string& name, const unsigned int& prereq_points, const unsigned int branches, ...);

    inline std::string name() const { return _name; }
    inline unsigned int level() const { return _level; }
    inline unsigned int prereq_points() const { return _prereq_points; }

    bool level_up();
    bool level_down();
    bool levellable() const;

    inline unsigned int branch_count() const { return _branch_count; }

    SkillBranch& operator[] (const unsigned int& i) const { return _branches[i]; }

    inline void set_tree(SkillTree* tree) { _tree = tree; }
private:
    Skill* _skill;
    SkillTree* _tree;
    std::string _name;

    unsigned int _prereq_points;
    unsigned int _level = 0;

    SkillBranch* _branches = new SkillBranch[1];
    unsigned int _branch_count = 0;
};

// A skill tree, linking Skills with pre/antirequisite skills
class SkillTree {
public:
    static SkillTree* get(const std::string& name);
    inline unsigned int total_points() const { return _total_points; }
    inline unsigned int unassigned_points() const { return _total_points - assigned_points(); }
    unsigned int assigned_points() const;

    inline std::string name() const { return _name; }
    SkillNode& operator[] (const std::string& i) { return _nodes[i]; }

    // Finds all base nodes of the skill tree
    std::string* bases(unsigned int* count) const;
    // Finds all nodes above (in no order)
    std::string* above(const SkillNode*) { return new std::string(); };
    // Finds all direct parents of the given node
    std::string* parents(const SkillNode*) { return new std::string(); };
    
    /* Imports a SkillTree from a file of the form:
    =============
    Name
    NodeCount
    Skill1 
    PrereqPoints 
    Branches
    Branch1
    Length
    Branch2 
    Length

    Skill2
    PrereqPoints 
    Branches
    Branch1
    Length
    Branch2 
    Length

    Skill3
    PrereqPoints 
    Branches
    Branch1
    Length
    Branch2 
    Length
    ...
    =============
    */
    static void import(const std::string& url);
private:
    SkillTree(const std::string& name, const unsigned int nodes, ...);
    std::string _name;
    unsigned int _total_points;
    std::map<std::string, SkillNode> _nodes;

    std::string* _bases;

    static std::map<std::string, SkillTree*> all_trees;
};