/* --------------------------------------------------------------------------
 * Get state representing substring s[l..r]
 *
 * Idea:
 *   - Start from the state of prefix ending at r (pos_state[r]).
 *   - Climb suffix links using binary lifting until state's length ≥ substring length.
 *
 * Returns:
 *   State id in SAM that corresponds exactly to substring s[l..r].
 * -------------------------------------------------------------------------- */
int get_state_substring(int l, int r) {
    int len = r - l + 1;
    int u = pos_state[r];
    for (int k = LOG - 1; k >= 0; --k) {
        int anc = up[u][k];
        if (st[anc].len >= len) u = anc;
    }
    return u;
}