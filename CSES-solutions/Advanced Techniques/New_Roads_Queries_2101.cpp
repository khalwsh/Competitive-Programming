/* problem statement text */
/*
CSES - New Roads Queries

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities in Byteland but no roads between them. However, each day, a new road will be built. There will be a total of mmm roads.
Your task is to process qqq queries of the form: "after how many days can we travel from city aaa to city bbb for the first time?"
Input
The first input line has three integers nnn, mmm and qqq: the number of cities, roads and queries. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines that describe the roads in the order they are built. Each line has two integers aaa and bbb: there will be a road between cities aaa and bbb.
Finally, there are qqq lines that describe the queries. Each line has two integers aaa and bbb: we want to travel from city aaa to city bbb.
Output
For each query, print the number of days, or −1-1−1 if it is never possible.
Constraints

1≤n,m,q≤2⋅1051 \le n, m, q \le 2 \cdot 10^51≤n,m,q≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 4 3
1 2
2 3
1 3
2 5
1 3
3 4
3 5

Output:
2
-1
4
*/
#include <bits/stdc++.h>
using namespace std;
 
struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
 
    void init(int n_) {
        n = n_;
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
 
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
 
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
 
    bool same(int a, int b) { return find(a) == find(b); }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#if !defined(ONLINE_JUDGE)
    // optional: comment out if not using local files
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
#endif
 
    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    vector<pair<int, int> > edges(m + 1);
    for (int i = 1; i <= m; ++i) cin >> edges[i].first >> edges[i].second;
 
    vector<pair<int, int> > queries(q);
    for (int i = 0; i < q; ++i) cin >> queries[i].first >> queries[i].second;
 
    // Results and binary search bounds: we will search in [1..m+1]
    // m+1 indicates "never"
    const int INF_DAY = m + 1;
    vector<int> L(q, 1), R(q, INF_DAY);
 
    // handle trivial queries a==b => answer 0 immediately (not part of binary search)
    // We'll store final answers in ans; if ans == 0 -> same city; if ans == m+1 -> -1
    vector<int> ans(q, -1);
    vector<char> fixed(q, 0);
    for (int i = 0; i < q; ++i) {
        if (queries[i].first == queries[i].second) {
            ans[i] = 0;
            fixed[i] = 1;
            // mark bounds so it's not processed
            L[i] = R[i] = 0;
        }
    }
 
    // Parallel binary search iterative
    bool changed = true;
    DSU dsu(n);
    while (true) {
        // buckets for mids 1..m+1 (index m+1 included)
        vector<vector<int> > bucket(m + 2);
        bool any = false;
        for (int i = 0; i < q; ++i) {
            if (fixed[i]) continue;
            if (L[i] < R[i]) {
                int mid = (L[i] + R[i]) >> 1;
                bucket[mid].push_back(i);
                any = true;
            }
        }
        if (!any) break;
 
        dsu.init(n);
        // iterate days 1..m and then process bucket[m+1] after all edges
        for (int day = 1; day <= m + 1; ++day) {
            if (day <= m) {
                dsu.unite(edges[day].first, edges[day].second);
            }
            for (int qi: bucket[day]) {
                auto [a,b] = queries[qi];
                if (dsu.same(a, b)) {
                    // connected by 'day', so upper bound reduces to day
                    R[qi] = day;
                } else {
                    // not connected by day => need later
                    L[qi] = day + 1;
                }
            }
        }
 
        // mark those that finished (L==R) as fixed and set ans
        for (int i = 0; i < q; ++i) {
            if (fixed[i]) continue;
            if (L[i] == R[i]) {
                fixed[i] = 1;
                ans[i] = L[i]; // may be m+1 meaning never
            }
        }
    }
 
    // output
    for (int i = 0; i < q; ++i) {
        if (ans[i] == 0) {
            cout << 0 << '\n';
        } else if (ans[i] == INF_DAY) {
            cout << -1 << '\n';
        } else {
            cout << ans[i] << '\n';
        }
    }
 
    return 0;
}