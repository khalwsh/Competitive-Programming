// get the number of distinct substrings
ll distinct_sub_strings() {
    long long tot = 0;
    for (int i = 1; i < sz; i++) {
        tot += st[i].len - st[st[i].link].len;
    }
    return tot;
}