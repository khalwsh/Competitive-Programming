vector<int>fp(vector<int>&per , vector<int>&seq , ll k) {
    auto apply = [&](vector<int>&a , vector<int>&b) {
        vector<int>na(a.size());
        for (int j = 0;j < b.size();j++) {
            na[j] = a[b[j] - 1];
        }
        return na;
    };
    auto res = per;
    while (k) {
        if (k & 1) {
            res = apply(res , seq);
        }
        seq = apply(seq , seq);
        k >>= 1;
    }
    return res;
}