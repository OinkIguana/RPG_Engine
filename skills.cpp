#include "skills.h"

std::map<std::string, Skill*> Skill::all_skills;
std::map<std::string, SkillTree*> SkillTree::all_trees;

Skill* Skill::get(const std::string& name) {
    auto old = all_skills.find(name);
    if (old != all_skills.end()) {
        return old->second;
    }
    return nullptr;
}

void Skill::import(const std::string& url) {
    std::ifstream file(url);
    while (!file.eof()) {
        std::string name = "", desc = "";
        unsigned int level;
        while (name == "") {
            getline(file, name);
        }
        while (desc == "") {
            getline(file, desc);
        }
        file >> level;
        all_skills[name] = new Skill(name, desc, level);
    }
}

unsigned int SkillTree::assigned_points() const {
    unsigned int n = 0;
    for (auto i : _nodes) {
        n += i.second.level();
    }
    return n;
}

std::string* SkillTree::bases(unsigned int* count) const { return _bases; }

SkillNode::SkillNode(const std::string& name, const unsigned int& prereq_points, const unsigned int branches, ...) 
    : _name(name), _prereq_points(prereq_points), _branch_count(branches), _skill(Skill::get(name)) {
    _branches = new SkillBranch[branches];
    va_list br;
    va_start(br, branches);
    for (unsigned int i = 0; i < branches; i++) {
        _branches[i] = va_arg(br, SkillBranch);
    }
    va_end(br);
}

bool SkillNode::level_up() {
    if (_level == _skill->max_level()) { return false; }
    if (!levellable()) { return false; }
    _level++;
    return true;
}

bool SkillNode::level_down() {
    if (_level == 0) { return false; }
    _level--;
    return true;
}

bool SkillNode::levellable() const {
    std::string* above = _tree->above(this);
    delete[] above;
    return false;
}

SkillTree* SkillTree::get(const std::string& name) {
    auto old = all_trees.find(name);
    if (old != all_trees.end()) {
        return old->second;
    }
    return nullptr;
}

void SkillTree::import(const std::string& url) {
    std::ifstream file(url);
    while (!file.eof()) {
        std::string name = "";
        unsigned int nodes;
        while (name == "") {
            getline(file, name);
        }
        all_trees[name] = new SkillTree(name, 0);

        file >> nodes;
        for (unsigned i = 0; i < nodes; i++) {
            std::string skill = "";
            while (skill == "") {
                getline(file, skill);
            }
            all_trees[name]->_nodes[skill] = SkillNode(skill);
            file >> all_trees[name]->_nodes[skill];
        }
    }
}

std::istream& operator>>(std::istream& file, SkillNode& node) {
    file >> node._prereq_points;
    file >> node._branch_count;
    node._branches = new SkillBranch[node._branch_count];
    for (unsigned int i = 0; i < node._branch_count; i++) {
        file >> node._branches[i];
    }
    return file;
}

std::istream& operator>>(std::istream& file, SkillBranch& branch) {
    while (branch._end == "") {
        getline(file, branch._end);
    }
    file >> branch._length;
    return file;
}

SkillTree::SkillTree(const std::string& name, const unsigned int nodes, ...) : _name(name) {
    std::map<std::string, bool> base_candidates;
    va_list nd;
    va_start(nd, nodes);
    for (unsigned int i = 0; i < nodes; i++) {
        SkillNode n = va_arg(nd, SkillNode);
        _nodes[n.name()] = n;
        _nodes[n.name()].set_tree(this);
        if (n.prereq_points() == 0 && base_candidates[n.name()] != false) {
            base_candidates[n.name()] = true;
        }
    }
    va_end(nd);
}