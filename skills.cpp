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

std::string* SkillTree::above(const SkillNode* node, unsigned int* count) {
    std::map<std::string, bool> visited;
    std::map<std::string, bool> is;
    is[node->name()] = visited[node->name()] = true;
    std::function<bool(const std::string&)> next = [&](const std::string& current_node) {
        if (visited[current_node]) { return is[current_node]; }
        visited[current_node] = true;
        for (unsigned int i = 0; i < _nodes[current_node].branch_count(); i++) {
            is[current_node] = is[current_node] || next(_nodes[current_node][i].end());
        }
        return is[current_node];
    };
    for (unsigned int i = 0; i < _bases_count; i++) {
        next(_bases[i]);
    }
    unsigned int n = 0;
    for (auto i : is) {
        if (i.second) {
            n++;
        }
    }
    std::string* ret = new std::string[(*count) = n];
    for (auto i : is) {
        if (i.second) {
            ret[--n] = i.first;
        }
    }
    return ret;
}

std::string* SkillTree::parents(const SkillNode* node, unsigned int* count) {
    auto i = _nodes.begin();
    std::function<void()> next;
    std::string* ret;
    unsigned int n = 0;
    (next = [&] {
        if (i == _nodes.end()) {
            ret = new std::string[n];
            *count = n;
            return;
        }
        bool is = false;
        for (unsigned int j = 0; j < i->second.branch_count(); j++) {
            if (i->second[j].end() == node->name()) {
                is = true;
                ++n;
                break;
            }
        }
        ++i;
        next();
        --i;
        if (is) { ret[--n] = i->first; }
    })();
    return ret;
}

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

bool SkillNode::levellable() const {
    unsigned int n;
    std::string* above = _tree->above(this, &n);
    unsigned int x = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (above[i] != _name) {
            x += (*_tree)[above[i]]._level;
        }
    }
    delete[] above;
    if (x < _prereq_points) { return false; }
    bool ok = false;
    std::string* parents = _tree->parents(this, &n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < (*_tree)[parents[i]]._branch_count; j++) {
            if ((*_tree)[parents[i]]._level == (*_tree)[parents[i]][j].length()) {
                ok = true;
                goto end_loop;
            }
        }
    }
end_loop:
    delete[] parents;
    return ok;
}

bool SkillNode::level_down() {
    if (_level == 0) { return false; }
    _level--;
    return true;
}

bool SkillNode::valid() const {
    std::function<bool(const SkillNode*)> next;
    std::map<const SkillNode*, bool> visited;
    std::map<const SkillNode*, bool> ok;
    return (next = [&next, &visited, &ok](const SkillNode* node) -> bool {
        // Already checked this node
        if (visited[node]) { return ok[node]; }
        visited[node] = true;
        // Totally bad
        if (node->_level > node->_skill->max_level()) { return ok[node] = false; }
        // Check prerequisite points
        unsigned int n;
        std::string* above = node->_tree->above(node, &n);
        unsigned int x = 0;
        for (unsigned int i = 0; i < n; i++) {
            if (above[i] != node->_name) {
                x += (*(node->_tree))[above[i]]._level;
            }
        }
        delete[] above;
        if (x < node->_prereq_points) { return ok[node] = false; }
        // Check at least one parent branch is extended enough
        bool branch_length_ok = false;
        std::string* parents = node->_tree->parents(node, &n);
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < (*(node->_tree))[parents[i]]._branch_count; j++) {
                if ((*(node->_tree))[parents[i]]._level == (*(node->_tree))[parents[i]][j].length()) {
                    branch_length_ok = true;
                    goto end_loop;
                }
            }
        }
    end_loop:
        delete[] parents;
        if (!branch_length_ok) { return ok[node] = false; }
        // This node is ok, given itself only
        ok[node] = true;
        // Check children
        for (unsigned int i = 0; i < node->_branch_count; i++) {
            if (!next(&(*(node->_tree))[node->_branches[i].end()])) {
                return ok[node] = false;
            }
        }
        return ok[node];
    })(this);
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
        all_trees[name]->_set_bases();
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
    va_list nd;
    va_start(nd, nodes);
    for (unsigned int i = 0; i < nodes; i++) {
        SkillNode n = va_arg(nd, SkillNode);
        _nodes[n.name()] = n;
        _nodes[n.name()].set_tree(this);
    }
    va_end(nd);
    _set_bases();
}

void SkillTree::_set_bases() {
    std::map<std::string, bool> not_base;
    unsigned int n = 0;
    for (auto i = _nodes.begin(); i != _nodes.end(); i++) {
        if (i->second.prereq_points() != 0) {
            not_base[i->second.name()] = true;
        }
        for (unsigned int j = 0; j < i->second.branch_count(); j++) {
            not_base[i->second[j].end()] = true;
        }
    }
    for (auto i = _nodes.begin(); i != _nodes.end(); i++) {
        if (!not_base[i->first]) {
            n++;
        }
    }
    _bases = new std::string[n];
    _bases_count = n;
    for (auto i = _nodes.begin(); i != _nodes.end(); i++) {
        if (!not_base[i->first]) {
            _bases[--n] = i->first;
        }
    }
}