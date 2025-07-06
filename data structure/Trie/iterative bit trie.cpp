const int BITS = 30;

class BinaryTrie {
private:
    struct TrieNode {
        TrieNode* child[2];
        int cnt;
        TrieNode() : cnt(0) {
            child[0] = child[1] = nullptr;
        }
    };
    TrieNode* root;
public:
    BinaryTrie() {
        root = new TrieNode();
    }
    void insert(int num) {
        TrieNode* cur = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!cur->child[bit]) {
                cur->child[bit] = new TrieNode();
            }
            cur = cur->child[bit];
            cur->cnt++;
        }
    }
    void remove(int num) {
        TrieNode* cur = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            TrieNode* next = cur->child[bit];
            next->cnt--;
            cur = next;
        }
    }
    int query(int num) { // max_xor
        TrieNode* cur = root;
        int ans = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int toggled = bit ^ 1;
            if (cur->child[toggled] && cur->child[toggled]->cnt > 0) {
                ans |= (1ll << i); // if you want min xor move this to else if
                cur = cur->child[toggled];
            } else if (cur->child[bit]) {
                cur = cur->child[bit];
            } else {
                break;
            }
        }
        return ans;
    }
} tr;