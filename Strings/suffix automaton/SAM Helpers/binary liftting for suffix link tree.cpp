/* --------------------------------------------------------------------------
 * Build binary lifting table for suffix link tree
 * - up[k][i] is the 2^k-th ancestor of node i
 * Purpose:
 *   Allows fast traversal up suffix links (jumping in powers of 2).
 *   This is especially useful for substring → state queries.
 * -------------------------------------------------------------------------- */
void build_up() {
    up[0][0] = 0;
    for (int i = 1; i < sz; ++i) {
        up[i][0] = st[i].link;
    }

    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i < sz; ++i) {
            up[i][k] = up[up[i][k - 1]][k - 1];
        }
    }
}