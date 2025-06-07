struct Trie {
    Trie *link[2];
    int cnt;
    int leaf;
    Trie(const Trie& o) : cnt(o.cnt), leaf(o.leaf) {
        link[0] = o.link[0] ? new Trie(*o.link[0]) : nullptr;
        link[1] = o.link[1] ? new Trie(*o.link[1]) : nullptr;
    }
    static const int BITS = 30;
    Trie() {
        for (int i = 0; i < 2; ++i) {
            link[i] = nullptr;
        }
        cnt = 0;
        leaf = 0;
    }

    void insert(int x, int idx = BITS) {
        if (idx == -1) {
            cnt++;
            leaf++;
            return;
        }
        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr)link[ch] = new Trie();
        link[ch]->insert(x, idx - 1);

        cnt++;
    }

    bool erase(int x, int idx = BITS) {
        if (idx == -1) {
            cnt--;
            leaf--;
            return true;
        }

        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr) {
            return false;
        }
        if (link[ch]->erase(x, idx - 1)) {
            cnt--;
            if (link[ch]->cnt == 0) {
                delete link[ch];
                link[ch] = nullptr;
            }
            return true;
        }
        return false;
    }

    int find(int x, int idx = BITS) {
        if (idx == -1)return cnt;

        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr)return 0;
        return link[ch]->find(x, idx - 1);
    }

    int MinXor(int x, int idx = BITS) {
        if (idx == -1) {
            return 0;
        }

        bool ch = ((1ll << idx) & x);

        if (link[ch] != nullptr) {
            return link[ch]->MinXor(x, idx - 1);
        } else if (link[!ch] != nullptr)return link[!ch]->MinXor(x, idx - 1) | (1ll << idx);
        return x;
    }

    int MaxXor(int x, int idx = BITS) {
        if (idx == -1) {
            return 0;
        }

        bool ch = ((1ll << idx) & x);

        if (link[!ch] != nullptr) {

            return link[!ch]->MaxXor(x, idx - 1) | (1ll << idx);
        } else if (link[ch] != nullptr)return link[ch]->MaxXor(x, idx - 1);
        return 0;
    }


} ;