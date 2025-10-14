// maximize |substring| * frequency(substring)
// if you want to consider sending string t such that substrings ends with position where t[pos] = '1' doesn't count
// just when initialize cnt[cur] = 1 , make it if t[pos] = '0'
ll calc(string &s) {
    build(s);
    propagation();
    ll res = 0;
    for (int i = 1; i < sz; i++) {
        res = max(res, 1LL * st[i].len * cnt[i]);
    }
    return res;
// if you want to get the sequence itself 
// for (int i = st[s].first_pos - st[s].len + 1; i <= st[s].first_pos; i++)
//        cout << v[i] << " ";

}
