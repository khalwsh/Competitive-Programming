
/* Count distinct rotations of string t in SAM
 * - Rotation = t[k..n-1] + t[0..k-1], for 0 ≤ k < n
 * - Duplicate string (t + t - 1) and traverse SAM
 * - When match length ≥ n, find state for length-n substring
 * - Use vis[] to mark counted states, add cnt[state] once
 */
ll count_rotations(const string &t) {
    int n = (int) t.size();
    if (n == 0) return 0;

    string s = t + t;
    s.pop_back();
    int node = 0, cur_len = 0;
    ll ans = 0;
    vector<int> reset;

    for (int i = 0; i < (int) s.size(); ++i) {
        int ch = s[i] - 'a';
        while (node != -1 && st[node].nxt[ch] == -1) {
            node = st[node].link;
            if (node != -1) cur_len = st[node].len;
            else cur_len = 0;
        }

        if (node == -1) {
            break; // no need to continue;
        }

        node = st[node].nxt[ch];
        ++cur_len;

        if (cur_len < n) continue;

        while (st[node].link != -1 && st[st[node].link].len >= n) {
            node = st[node].link;
        }

        if (!vis[node]) {
            ans += cnt[node];
            vis[node] = true;
            reset.emplace_back(node);
        }
    }

    for (int x: reset) vis[x] = false;
    return ans;
}