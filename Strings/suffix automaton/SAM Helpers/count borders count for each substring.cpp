ll count_borders(string &s) {
    build(s);
    propagation();
    ll res = 0;
    for (int i = 1; i < sz; i++) {
        ll lg = st[i].len;
        ll sh = st[st[i].link].len + 1;
        res += (cnt[i] * (cnt[i] + 1) / 2) * (lg - sh + 1);
    }
    cout << res << '\n';
}