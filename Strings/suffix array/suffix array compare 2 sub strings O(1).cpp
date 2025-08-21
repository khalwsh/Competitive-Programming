template<typename T>
struct sparseTable {
    int sz, lg;
    vector<vector<T> > t;
    function<T(T, T)> combine;

    void init(int n, function<T(T, T)> F) {
        sz = n;
        lg = __lg(n);
        combine = F;
        t.resize(lg + 1, vector<T>(n + 1));
    }

    void build(vector<T> &v) {
        for (int i = 0; i < sz; i++) {
            // TODO 0-based
            t[0][i] = v[i];
        }
        for (int p = 1; p <= lg; p++) {
            for (int i = 0; i + (1 << p) <= sz; i++) {
                t[p][i] = combine(t[p - 1][i], t[p - 1][i + (1 << (p - 1))]);
            }
        }
    }

    // TODO 0-based
    T query(int l, int r) {
        assert(l <= r);
        int k = 31 - __builtin_clz(r - l + 1);
        return combine(t[k][l], t[k][r - (1 << k) + 1]);
    }
};
vector<int> buildSuffixArray(string s) {
    int n = s.size(); s += char(0);
    vector<int> p(n+1), c(n+1), c1(n+1), cnt(max(256, n+1)), p1(n+1);
    for(int i = 0; i <= n; i++) p[i] = i, c[i] = s[i];

    for(int k = 0; (1 << k) <= n; k++) {
        int len = 1 << k;

        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[min(n, p[i] + len)]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p1[--cnt[c[min(n, p[i] + len)]]] = p[i];

        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[p1[i]]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p[--cnt[c[p1[i]]]] = p1[i];

        c1[p[0]] = 0;
        for(int i = 1; i <= n; i++)
            c1[p[i]] = c1[p[i-1]] + (c[p[i]] != c[p[i-1]] || c[min(n,p[i]+len)] != c[min(n,p[i-1]+len)]);
        c.swap(c1);
        if(c[p[n]] == n) break;
    }

    vector<int> res;
    for(int i = 1; i <= n; i++) res.push_back(p[i]);
    return res;
}
vector<int> Kasai(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if(rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}

sparseTable<int> sp;
vector<int>rev;
void init(vector<int>& suf , vector<int>&lcp) {
    int n = suf.size();
    rev = vector<int>(n);
    for (int i = 0;i < n;i++) {
        rev[suf[i]] = i;
    }
    sp.init(lcp.size() , [&](int x , int y) -> int {
        return min(x , y);
    });
    sp.build(lcp);
}
int compare(const pair<int,int> &a, const pair<int,int> &b) {
    int A = rev[a.first];
    int B = rev[b.first];
    int la = a.second - a.first + 1;
    int lb = b.second - b.first + 1;

    if (A == B) {
        if (la == lb) return 0;
        return la < lb ? -1 : 1;
    }

    int l = min(A, B);
    int r = max(A, B) - 1;
    int mn = sp.query(l, r);

    int mnlen = min(la, lb);
    if (mn >= mnlen) {
        if (la == lb) return 0;
        return la < lb ? -1 : 1;
    } else {
        return A < B ? -1 : 1;
    }
}