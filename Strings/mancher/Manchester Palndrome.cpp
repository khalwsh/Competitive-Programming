struct Manacher {
    // p[i] : the radius info on transformed string (with '#' separators)
    // P[2 * j + 1] : palindrome info for jth character in string s , zero base
    // P[2 * j + 2] : palindrome info for the gap between j , j + 1 in string s
    vector<int> p;
    void build(string &s) {
        string t;
        for (auto &val : s) t += '#', t += val;
        t += '#';
        int n = (int)t.size();
        p.assign(n, 1);
        int l = 1, r = 1;
        for (int i = 1; i < n; i++) {
            p[i] = max(0, min(r - i, p[l + r - i]));
            while (i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) p[i]++;
            if (p[i] + i > r) {
                r = i + p[i];
                l = i - p[i];
            }
        }
    }
    int GetLongest(int center, bool odd = true) {
        int NewCenter = 2 * center + !odd + 1;
        return p[NewCenter] - 1;
    }
    bool IsPalndrome(int l, int r) {
        return (r - l + 1) <= GetLongest((l + r) / 2, l % 2 == r % 2);
    }
 
    ll countAll(string &s) {
        build(s);
        ll tot = 0;
        for (auto &val : p) tot += val / 2;
        return tot;
    }
};