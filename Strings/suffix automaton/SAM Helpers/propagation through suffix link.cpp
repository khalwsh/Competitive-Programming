/* --------------------------------------------------------------------------
 * cnt[u]
 * - Number of occurrences of the substring(s) represented by state u.
 * - Set cnt[cur] = 1 in sa_extend() and then call propagation()
 *   to accumulate counts via suffix links.
 * -------------------------------------------------------------------------- */
void propagation() {
    // Order states by length (longest → shortest)
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });

    for (int v: order) {
        if (st[v].link != -1) {
            cnt[st[v].link] += cnt[v];
        }
    }
}
