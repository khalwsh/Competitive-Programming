/* --------------------------------------------------------------------------
 * Get first position of a pattern in the text (1-based index)
 *
 * Traverses SAM along the characters of `pat`.
 * If traversal fails → pattern not found, return -1.
 * Otherwise → return (end_pos - |pat| + 2).
 * -------------------------------------------------------------------------- */
int get_first_pos(const string &pat) {
    int node = 0;
    for (auto &ch: pat) {
        int nxt = st[node].nxt[ch - 'a'];
        if (nxt == -1) return -1;
        node = nxt;
    }
    return st[node].first_pos - pat.size() + 2;
}