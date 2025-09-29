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