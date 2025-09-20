
const int MAXN = 100000 + 5;
const int MAXBIT = 29;

struct TNode {
    TNode *l, *r;
    int cnt;

    TNode() {
        cnt = 0;
        l = r = nullptr;
    }
};

TNode *roots[MAXN];

TNode *cloneNode(TNode *prev) {
    TNode *cur = new TNode();
    if (prev) {
        cur->l = prev->l;
        cur->r = prev->r;
        cur->cnt = prev->cnt;
    }
    return cur;
}

TNode *insertTrie(TNode *prevRoot, int val) {
    TNode *cur = cloneNode(prevRoot);
    cur->cnt = (prevRoot ? prevRoot->cnt : 0) + 1;
    TNode *root = cur;
    TNode *prev = prevRoot;
    for (int b = MAXBIT; b >= 0; --b) {
        int bit = (val >> b) & 1;
        TNode *prevChild = prev ? (bit ? prev->r : prev->l) : nullptr;
        TNode *newChild = cloneNode(prevChild);
        newChild->cnt = (prevChild ? prevChild->cnt : 0) + 1;
        if (bit) cur->r = newChild;
        else cur->l = newChild;
        cur = newChild;
        prev = prevChild;
    }
    return root;
}

int queryTrie(TNode *oldRoot, TNode *newRoot, int x) {
    int res = 0;
    TNode *oldCur = oldRoot;
    TNode *newCur = newRoot;
    for (int b = MAXBIT; b >= 0; --b) {
        int bit = (x >> b) & 1;
        int want = 1 - bit;
        TNode *newChild = want ? (newCur ? newCur->r : nullptr) : (newCur ? newCur->l : nullptr);
        TNode *oldChild = want ? (oldCur ? oldCur->r : nullptr) : (oldCur ? oldCur->l : nullptr);
        int have = (newChild ? newChild->cnt : 0) - (oldChild ? oldChild->cnt : 0);
        if (have > 0) {
            res |= (1 << b);
            newCur = newChild;
            oldCur = oldChild;
        } else {
            newCur = bit ? (newCur ? newCur->r : nullptr) : (newCur ? newCur->l : nullptr);
            oldCur = bit ? (oldCur ? oldCur->r : nullptr) : (oldCur ? oldCur->l : nullptr);
        }
    }
    return res;
}