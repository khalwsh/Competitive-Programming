// your treap should support range maximum
// it return index of first value >= x
int gtMax(Treap* root) {
    if (!root) return -2e9;
    return root -> mx;
}
int lower_bound(Treap* root, int x) {
    if (!root) return 0;
    if (gtMax(root->kids[0]) >= x) {
        // there exists some element >= x in left subtree -> go left
        return lower_bound(root->kids[0], x);
    }
    if (root->val >= x) return Size(root->kids[0]); // first element >= x is root
    return Size(root->kids[0]) + 1 + lower_bound(root->kids[1], x);
}

// kth element
char get(Treap* me, int k) {
    if (!me || k <= 0 || k > Size(me)) return '\0';
    prop(me);
    int lf = Size(me->kids[0]);
    if (k <= lf) return get(me->kids[0], k);
    if (k == lf + 1) return me->val;
    return get(me->kids[1], k - lf - 1);
}