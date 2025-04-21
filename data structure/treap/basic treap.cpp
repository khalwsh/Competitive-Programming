struct Treap {
    struct Node {
        int val, prior, size;
        bool rev;
        Node *l, *r;
        Node(int v) : val(v), prior(rand()), size(1), rev(false), l(nullptr), r(nullptr) {}
    };

    using pNode = Node*;
    pNode root = nullptr;

    Treap() : root(nullptr) {}

    int sz(pNode t) { return t ? t->size : 0; }

    void update(pNode t) {
        if (t) t->size = 1 + sz(t->l) + sz(t->r);
    }

    void push(pNode t) {
        if (t && t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = false;
        }
    }

    void split(pNode t, int k, pNode &l, pNode &r) {
        if (!t) return void(l = r = nullptr);
        push(t);
        if (sz(t->l) >= k) {
            split(t->l, k, l, t->l);
            r = t;
        } else {
            split(t->r, k - sz(t->l) - 1, t->r, r);
            l = t;
        }
        update(t);
    }

    pNode merge(pNode l, pNode r) {
        push(l); push(r);
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            update(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update(r);
            return r;
        }
    }

    // Inserts a new node with value 'val' at position 'pos'.
    void insert(int pos, int val) {
        pNode l, r;
        split(root, pos, l, r);
        root = merge(merge(l, new Node(val)), r);
    }

    // Updates the node at position 'pos' with a new value (if needed).
    void update_value(int pos, int new_val) {
        pNode l, mid, r;
        split(root, pos, l, r);
        split(r, 1, mid, r);
        if (mid) mid->val = new_val;
        root = merge(merge(l, mid), r);
    }

    // Returns the value at the given index.
    int query(int pos) {
        pNode l, mid, r;
        split(root, pos, l, r);
        split(r, 1, mid, r);
        int result = mid ? mid->val : -1; // or throw error if out-of-bounds
        root = merge(merge(l, mid), r);
        return result;
    }

    // Reverses the entire treap.
    void reverse_all() {
        if (root) root->rev ^= 1;
    }

    // Reverses the subrange [l_pos, r_pos] (inclusive)
    void reverse_range(int l_pos, int r_pos) {
        pNode l, mid, r;
        split(root, l_pos, l, r);
        split(r, r_pos - l_pos + 1, mid, r);
        if (mid) mid->rev ^= 1;
        root = merge(merge(l, mid), r);
    }

    // Moves the last element to the front (cyclic shift).
    void rotate_last_to_front() {
        if (sz(root) <= 1) return;
        pNode l, last;
        split(root, sz(root) - 1, l, last); // 'last' is the node at the end.
        root = merge(last, l);
    }
};
