/* --------------------------------------------------------------------------
 * Build adjacency list of the suffix link tree
 * - adj[i] contains all states whose suffix link points to i
 * -------------------------------------------------------------------------- */
void build_adj() {
    for (int i = 0; i < sz; ++i) adj[i].clear();
    for (int i = 1; i < sz; ++i) {
        adj[st[i].link].push_back(i);
    }
}