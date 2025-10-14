// kth substring , unique

ll dp[MAXN];

ll solve(int cur) {
    ll res = 1;
    ll &ret = dp[cur];
    if (~ret) return ret;
    for (int i = 0; i < 26; i++) {
        if (st[cur].nxt[i] != -1) {
            res += solve(st[cur].nxt[i]);
        }
    }
    return ret = res;
}

string res;

void build(int cur, ll rem) {
    if (rem <= 0) return;
    for (int i = 0; i < 26; i++) {
        int u = st[cur].nxt[i];
        if (u == -1) continue;
        ll cnt = solve(u);
        if (cnt >= rem) {
            res += char('a' + i);
            build(u, rem - 1);
            return;
        }
        rem -= cnt;
    }
}

string get(ll k) {
    ll all = solve(0) - 1;
    assert(all >= k);
    build(0, k);
    return res;
}