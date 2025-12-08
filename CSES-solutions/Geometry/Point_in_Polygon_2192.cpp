/* problem statement text */
/*
CSES - Point in Polygon

Time limit: 1.00 s
Memory limit: 512 MB

You are given a polygon of nnn vertices and a list of mmm points. Your task is to determine for each point if it is inside, outside or on the boundary of the polygon.
The polygon consists of nnn vertices (x1,y1),(x2,y2),…,(xn,yn)(x_1,y_1),(x_2,y_2),\dots,(x_n,y_n)(x1​,y1​),(x2​,y2​),…,(xn​,yn​). The vertices (xi,yi)(x_i,y_i)(xi​,yi​) and (xi+1,yi+1)(x_{i+1},y_{i+1})(xi+1​,yi+1​) are adjacent for i=1,2,…,n−1i=1,2,\dots,n-1i=1,2,…,n−1, and the vertices (x1,y1)(x_1,y_1)(x1​,y1​) and (xn,yn)(x_n,y_n)(xn​,yn​) are also adjacent.
Input
The first input line has two integers nnn and mmm: the number of vertices in the polygon and the number of points.
After this, there are nnn lines that describe the polygon. The iiith such line has two integers xix_ixi​ and yiy_iyi​.
You may assume that the polygon is simple, i.e., it does not intersect itself.
Finally, there are mmm lines that describe the points. Each line has two integers xxx and yyy.
Output
For each point, print "INSIDE", "OUTSIDE" or "BOUNDARY".
Constraints

3≤n,m≤10003 \le n,m \le 10003≤n,m≤1000
1≤m≤10001 \le m \le 10001≤m≤1000
−109≤xi,yi≤109-10^9 \le x_i, y_i \le 10^9−109≤xi​,yi​≤109
−109≤x,y≤109-10^9 \le x, y \le 10^9−109≤x,y≤109

Example
Input:
4 3
1 1
4 2
3 5
1 4
2 3
3 1
1 3

Output:
INSIDE
OUTSIDE
BOUNDARY
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
static inline __int128 cross128(ll ax, ll ay, ll bx, ll by) {
    return (__int128)ax * by - (__int128)ay * bx;
}
 
static inline __int128 orient(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& p) {
    ll ax = b.first - a.first;
    ll ay = b.second - a.second;
    ll bx = p.first - a.first;
    ll by = p.second - a.second;
    return cross128(ax, ay, bx, by);
}
 
bool on_segment(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& p) {
    if (orient(a,b,p) != 0) return false;
    // check bounding box
    ll minx = min(a.first, b.first), maxx = max(a.first, b.first);
    ll miny = min(a.second, b.second), maxy = max(a.second, b.second);
    return (p.first >= minx && p.first <= maxx && p.second >= miny && p.second <= maxy);
}
 
// 0 = OUTSIDE, 1 = INSIDE, 2 = BOUNDARY
int point_in_polygon(const vector<pair<ll,ll>>& poly, const pair<ll,ll>& p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (on_segment(poly[i], poly[j], p)) return 2;
    }
 
    long long wn = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ll yi = poly[i].second, yj = poly[j].second;
        if (yi <= p.second) {
            if (yj > p.second) {
                __int128 o = orient(poly[i], poly[j], p);
                if (o > 0) ++wn;
            }
        } else {
            if (yj <= p.second) {
                __int128 o = orient(poly[i], poly[j], p);
                if (o < 0) --wn;
            }
        }
    }
    return wn == 0 ? 0 : 1;
}
 
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    vector<pair<ll,ll>> poly(n);
    for (int i = 0; i < n; ++i) cin >> poly[i].first >> poly[i].second;
    for (int i = 0; i < m; ++i) {
        pair<ll,ll> pt;
        cin >> pt.first >> pt.second;
        int ans = point_in_polygon(poly, pt);
        if (ans == 2) cout << "BOUNDARY\n";
        else if (ans == 1) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";
    }
}