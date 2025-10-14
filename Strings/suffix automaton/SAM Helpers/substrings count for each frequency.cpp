
// build for each frequency number of substrings with that frequency
// then multiply by i for repeating (like aaeddf , a exist 2 so *i to count it twice)
// then build suffix sum to handle queries of at least with frequency x
ll p[2 * MAXN];
void freq(string &s) {
    for (int i = 1; i <= s.size(); i++) p[i] = 0;
    build(s);
    propagation();
    for (int i = 1; i < sz; i++) {
        p[cnt[i]] += st[i].len - st[st[i].link].len;
    }
    for (int i = 1; i <= s.size(); i++) p[i] *= i;
    for (int i = s.size(); i >= 1; i--) { p[i - 1] += p[i]; }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << p[x] << '\n';
    }
}