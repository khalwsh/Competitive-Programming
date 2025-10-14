// return the number of substrings that frequency of substring % |substring| = 0
ll calc(string &s) {
    build(s);
    propagation();
    ll res = 0;
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            adj[j].emplace_back(i);
        }
    }
    for (int i = 1; i < sz; i++) {
        int sh = st[st[i].link].len + 1;
        int lg = st[i].len;
        res += 1LL * (upper_bound(adj[cnt[i]].begin(), adj[cnt[i]].end(), lg) - lower_bound(
                          adj[cnt[i]].begin(), adj[cnt[i]].end(), sh)) * cnt[i];
    }
    return res;
}