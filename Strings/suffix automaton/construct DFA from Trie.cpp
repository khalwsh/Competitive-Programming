
struct Trie {
    Trie *nxt[26]{};
    bool isEnd = false;
};

Trie *root = new Trie();

void insert(string &s) {
    Trie *cur = root;
    for (auto &val: s) {
        if (cur->nxt[val - 'a'] == nullptr) cur->nxt[val - 'a'] = new Trie();
        cur = cur->nxt[val - 'a'];
    }
    cur->isEnd = true;
}

struct NodeState {
    bool isEnd = false;
    Trie *targets[26]{};
    bool operator<(const NodeState &other) const {
        if (isEnd != other.isEnd) return isEnd < other.isEnd;
        for (int i = 0; i < 26; ++i) {
            if (targets[i] != other.targets[i]) {
                return targets[i] < other.targets[i];
            }
        }
        return false;
    }
};

map<NodeState, Trie *> canonical_nodes;
// it return the DFA root node (the structure is DAG)
Trie *DFA(Trie *cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    NodeState current_state;
    current_state.isEnd = cur->isEnd;
    for (int i = 0; i < 26; ++i) {
        current_state.targets[i] = DFA(cur->nxt[i]);
    }
    auto it = canonical_nodes.find(current_state);
    if (it != canonical_nodes.end()) {
        return it->second;
    } else {
        Trie *new_node = new Trie();
        new_node->isEnd = current_state.isEnd;
        for (int i = 0; i < 26; ++i) {
            new_node->nxt[i] = current_state.targets[i];
        }
        canonical_nodes[current_state] = new_node;
        return new_node;
    }
}