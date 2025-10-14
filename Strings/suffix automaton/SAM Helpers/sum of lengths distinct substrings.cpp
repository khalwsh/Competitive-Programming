// sum of lengths of distinct substrings
ll distinct_lengths() {
    ll tot = 0;
    for (int i = 1; i < sz; i++) {
        ll shortest = st[st[i].link].len + 1;
        ll longest = st[i].len;

        ll num_strings = longest - shortest + 1;
        ll cur = num_strings * (longest + shortest) / 2;
        tot += cur;
    }
    return tot;
}