/* problem statement text */
/*
CSES - Line Segments Trace II

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn line segments whose endpoints have integer coordinates. Each x-coordinate is between 000 and mmm. The slope of each segment is an integer.
For each x-coordinate 0,1,…,m0,1,\dots,m0,1,…,m, find the maximum point in any line segment. If there is no segment at some point, the maximum is −1-1−1.
Input
The first line has two integers nnn and mmm: the number of line segments and the maximum x-coordinate.
The next nnn lines describe the line segments. Each line has four integers x1x_1x1​, y1y_1y1​, x2x_2x2​ and y2y_2y2​: there is a line segment between points (x1,y1)(x_1,y_1)(x1​,y1​) and (x2,y2)(x_2,y_2)(x2​,y2​).
Output
Print m+1m+1m+1 integers: the maximum points for x=0,1,…,mx=0,1,\dots,mx=0,1,…,m.
Constraints

1≤n,m≤1051 \le n, m \le 10^51≤n,m≤105
0≤x1<x2≤m0 \le x_1 < x_2 \le m0≤x1​<x2​≤m
0≤y1,y2≤1090 \le y_1,y_2 \le 10^90≤y1​,y2​≤109

Example
Input:
4 5
1 1 3 3
1 2 4 2
2 4 5 7
2 8 5 2

Output:
-1 2 8 6 6 7
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF_LL = (ll)4e18;
 
struct LiChaoMax {
    struct Line { ll m, b; };
    int n;
    vector<ll> xs;
    vector<Line> st;
 
    LiChaoMax(const vector<ll>& coords) {
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
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> segs(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segs[i] = {x1, y1, x2, y2};
    }
    vector<ll> xs(m+1);
    for (int x = 0; x <= m; x++) xs[x] = x;
 
    LiChaoMax lichao(xs);
    for (auto& seg : segs) {
        ll x1, y1, x2, y2;
        tie(x1, y1, x2, y2) = seg;
        ll dx = x2 - x1;
        ll dy = y2 - y1;
        ll a = dy / dx;
        ll b = y1 - a * x1;
        lichao.add_segment(a, b, x1, x2 + 1);
    }
 
    for (int x = 0; x <= m; x++) {
        ll ans = lichao.query(x);
        if (ans < -INF_LL/2) cout << -1;
        else cout << ans;
        if (x < m) cout << ' ';
    }
    cout << '\n';
    return 0;
}