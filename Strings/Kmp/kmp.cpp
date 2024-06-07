struct KMP {
    //keywords: substring , prefix , suffix , equality
    //typically processing for the pattern similar to the input
    //try: s , s + s , rev(s) , s + 'a' + s ,....

    vector<int> failure;

    void build(const string &s) {
        int n = (int) s.size();
        if (failure.size() <= s.size())failure.clear(), failure.resize(n);
        for (int i = 1; i < n; i++) {
            int j = failure[i - 1];
            while (j > 0 && s[i] != s[j])
                j = failure[j - 1];
            if (s[i] == s[j])
                j++;
            failure[i] = j;
        }
    }

    vector<int> pattern(const string &s, const string &t) {
        build(t);
        int n = (int) s.size(), m = (int) t.size(), k = 0;
        vector<int> pos;
        for (int i = 0; i < n; i++) {
            while (k > 0 && s[i] != t[k]) {
                k = failure[k - 1];
            }
            if (s[i] == t[k])k++;
            if (k == m) {
                pos.emplace_back(i - m + 1);
                k = failure[k - 1];
            }
        }
        return pos;
    }

    static int LongestPalndromeSuffix(const string &s) {
        KMP temp;
        string rev = s;
        reverse(rev.begin(), rev.end());
        string x = rev + '@' + s;
        temp.build(x);
        return temp.failure[x.size() - 1];
    }

    static int LongestPalndromePrefix(const string &s) {
        KMP temp;
        string rev = s;
        reverse(rev.begin(), rev.end());
        string x = s + '@' + rev;
        temp.build(x);
        return temp.failure[x.size() - 1];
    }

    static int AddBackToBePalndrome(const string &s) {
        return (int) s.size() - LongestPalndromeSuffix(s);
    }

    static int AddFrontToBePalndrome(const string &s) {
        return (int) s.size() - LongestPalndromePrefix(s);
    }

    static int AddAnyToBePalndrome(const string &s) {
        // given a string you can add either to the back or front what's the min no of chars to add to make it palndrome
        return (int) s.size() - max(LongestPalndromePrefix(s), LongestPalndromeSuffix(s));
    }

    static int MinUnit(const string &s) {
        // what is the smallest prefix can build up the string
        KMP temp;
        temp.build(s);
        if (s.size() % (s.size() - temp.failure[s.size() - 1]) != 0)return (int) s.size();
        return (int) s.size() - temp.failure[s.size() - 1];
    }

    static int MinUnitVersion2(const string &s) {
        KMP temp;
        string p = s + s;
        vector<int> res = temp.pattern(p, s);
        if (res.size() >= 2)return res[1];
        else return (int) s.size();
    }

    static vector<int> FreqAllPrefixes(const string &s) {
        // count for every prefix it's frequency as sub string and count it self
        KMP temp;
        temp.build(s);
        vector<int> freq(s.size() + 1);
        for (int i = 0; i < s.size(); i++) {
            ++freq[temp.failure[i]];
        }
        for (int i = (int) s.size() - 1; i > 0; i--) {
            freq[temp.failure[i - 1]] += freq[i];
        }
        freq.erase(freq.begin());
        for (auto &val: freq)val++;
        return freq;
    }
    static int CountUniquePrefixes(const string &s){
        vector<int> temp = KMP::FreqAllPrefixes(s);
        return count(temp.begin() , temp.end() , 1);
    }
    static int UniqueSubStrings(const string &s){
        string temp = s;
        reverse(temp.begin() , temp.end());
        string cur;
        int n = (int)s.size();
        int res = 0;
        for(int i = n - 1;i>=0;i--){
            cur += temp[i];
            res += CountUniquePrefixes(cur);
        }
        return res;
    }
};
