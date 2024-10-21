struct Manacher {
    vector<int> p;
    string T;

    void build(string &s) {
        string t;
        T = s;
        for (auto &val : s) t += '#', t += val;
        t += '#';
        int n = t.size();
        p.resize(n, 0);
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            p[i] = (i < r) ? min(r - i, p[l + r - i]) : 1;
            while (i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) p[i]++;
            if (i + p[i] > r) {
                r = i + p[i];
                l = i - p[i];
            }
        }
    }

    int GetLongest(int center, bool odd = true) {
        int newCenter = 2 * center + !odd + 1;
        return p[newCenter] - 1;
    }

    bool IsPalindrome(int l, int r) {
        return (r - l + 1) <= GetLongest((l + r) / 2, l % 2 == r % 2);
    }

    string LongestPalindromeSubStr() {
        int maxLength = 0, start = -1;
        for (int i = 0; i < T.size(); i++) {
            if (GetLongest(i, false) > maxLength) {
                maxLength = GetLongest(i, false);
                start = i;
            }
            if (GetLongest(i, true) > maxLength) {
                maxLength = GetLongest(i, true);
                start = i;
            }
        }

        if (maxLength % 2 == 1) {
            return T.substr(start - maxLength / 2, maxLength);
        }
        return T.substr(start - maxLength / 2 + 1, maxLength);
    }
};