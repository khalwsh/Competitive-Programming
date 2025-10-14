// kth substring , Not unique , build cnt and propagate first
ll dp[MAXN];

ll solve(int v) {
    if (dp[v] != -1) return dp[v];
    ll res = 0;
    for (int c = 0; c < 26; c++) {
        int u = st[v].nxt[c];
        if (u != -1) {
            res += cnt[u]; // substrings of length 1 from this edge
            res += solve(u); // longer substrings
        }
    }
    return dp[v] = res;
}

void printKth(int v, ll k) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int u = st[v].nxt[ch - 'a'];
        if (u == -1) continue;
        ll total = cnt[u] + solve(u);
        if (k <= total) {
            cout << ch;
            if (k <= cnt[u]) return; // stop here
            printKth(u, k - cnt[u]);
            return;
        } else {
            k -= total;
        }
    }
}