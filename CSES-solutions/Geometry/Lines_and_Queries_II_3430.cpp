/* problem statement text */
/*
CSES - Lines and Queries II

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to efficiently process the following types of queries:

Add a line ax+bax+bax+b that is active in range [l,r][l,r][l,r]
Find the maximum point in any active line at position xxx

Input
The first line has an integer nnn: the number of queries.
The following nnn lines describe the queries. The format of each line is either "1 aaa bbb lll rrr" or "2 xxx".
Output
Print the answer for each query of type 2. If no line is active, print NO.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤a,b≤109-10^9 \le a,b \le 10^9−109≤a,b≤109
0≤x≤1050 \le x \le 10^50≤x≤105
0≤l≤r≤1050 \le l \le r \le 10^50≤l≤r≤105

Example
Input:
6
1 1 2 1 3
2 3
2 4
1 0 4 1 5
2 3
2 4

Output:
5
NO
5
4
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
// you build the Li-chao on the points x-coordinates you will query on them and then add segments and query
// note r is exculsive so adding segment in [l , r] should pass [l , r + 1]
// it will return -INF_LL in case no active line in range
const ll INF_LL = 1LL << 61;
struct LiChao {
    struct Line { ll m, b; };
private:
    void insert(int p, int l, int r, Line ln) {
        int m = (l + r) >> 1;
        ll xl = xs[l], xm = xs[m], xr = xs[r-1];
        Line& cur = st[p];
        if (eval(ln, xm) > eval(cur, xm)) swap(cur, ln);
        if (r - l == 1) return;
        if (eval(ln, xl) > eval(cur, xl))
            insert(p<<1, l, m, ln);
        else if (eval(ln, xr) > eval(cur, xr))
            insert(p<<1|1, m, r, ln);
    }
 
    void insert_seg(int p, int l, int r, Line ln, int ql, int qr) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            insert(p, l, r, ln);
            return;
        }
        int m = (l + r) >> 1;
        insert_seg(p<<1, l, m, ln, ql, qr);
        insert_seg(p<<1|1, m, r, ln, ql, qr);
    }
 
    ll query_point(int p, int l, int r, ll xq, int idx) const {
        ll res = eval(st[p], xq);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (idx < m)
            res = max(res, query_point(p<<1, l, m, xq, idx));
        else
            res = max(res, query_point(p<<1|1, m, r, xq, idx));
        return res;
    }
public:
    int n;
    vector<ll> xs;
    vector<Line> st;
 
    LiChao(const vector<ll>& coords) {
        xs = coords;
        n = xs.size();
        st.assign(4 * n, {0, -INF_LL});
    }
 
    ll eval(const Line& ln, ll x) const {
        return ln.m * x + ln.b;
    }
 
    void add_line(ll m, ll b) {
        insert(1, 0, n, {m, b});
    }
 
    void add_segment(ll m, ll b, ll xl, ll xr) {
        int L = lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (L < R) insert_seg(1, 0, n, {m, b}, L, R);
    }
 
    ll query(ll xq) const {
        int idx = lower_bound(xs.begin(), xs.end(), xq) - xs.begin();
        return query_point(1, 0, n, xq, idx);
    }
};
 
 
int main() {
    PRE();
    int n;cin >> n;
    vector<ll>coords;
    vector<array<int , 4>>queries;
    for (int i = 0;i < n;i++) {
        int t;cin >> t;
        if (t == 1) {
            int a , b; cin >> a >> b;
            int l , r; cin >> l >> r;
            queries.emplace_back(array<int , 4>{a , b , l , r});
        }else {
            int x;cin >> x;
            queries.emplace_back(array<int , 4>{x , 1000000001 ,1000000001 ,1000000001});
            coords.emplace_back(x);
        }
    }
    sort(coords.begin() , coords.end());
    coords.erase(unique(coords.begin() , coords.end()) , coords.end());
    LiChao root(coords);
    for (auto &val : queries) {
        if (val[1] == 1000000001) {
            auto x = root.query(val[0]);
            if (x <= -INF_LL / 2) cout << "NO\n";
            else cout << x << '\n';
        }else{
            root.add_segment(val[0] , val[1] , val[2] , val[3] + 1);
        }
    }
}