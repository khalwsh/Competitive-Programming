// returns longest common substring of vs (size >= 1). Assumes lowercase 'a'..'z'.
string longest_common_substring(const vector<string> &vs) {
    build(vs[0]);
    int nstates = sz;
    vector<int> mn(nstates);
    for (int i = 0; i < nstates; ++i) mn[i] = st[i].len;
    vector<int> order(nstates);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });
    for (size_t si = 1; si < vs.size(); ++si) {
        const string &t = vs[si];
        vector<int> best(nstates, 0);
        int v = 0, l = 0;
        for (char ch: t) {
            int letter = ch - 'a';
            if (st[v].nxt[letter] != -1) {
                v = st[v].nxt[letter];
                ++l;
            } else {
                while (v != -1 && st[v].nxt[letter] == -1) v = st[v].link;
                if (v == -1) {
                    v = 0;
                    l = 0;
                } else {
                    l = st[v].len + 1;
                    v = st[v].nxt[letter];
                }
            }
            best[v] = max(best[v], l);
        }
        for (int u: order) {
            int p = st[u].link;
            if (p != -1) {
                best[p] = max(best[p], min(best[u], st[p].len));
            }
        }
        for (int i = 0; i < nstates; ++i) {
            mn[i] = min(mn[i], best[i]);
        }
    }
    int bestlen = 0, beststate = 0;
    for (int i = 0; i < nstates; ++i) {
        if (mn[i] > bestlen) {
            bestlen = mn[i];
            beststate = i;
        }
    }
    if (bestlen == 0) return "";
    int pos = st[beststate].first_pos;
    return vs[0].substr(pos - bestlen + 1, bestlen);
}