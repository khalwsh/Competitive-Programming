/* problem statement text */
/*
CSES - Minimum Euclidean Distance

Time limit: 1.00 s
Memory limit: 512 MB

Given a set of points in the two-dimensional plane, your task is to find the minimum Euclidean distance between two distinct points.
The Euclidean distance of points (x1,y1)(x_1,y_1)(x1​,y1​) and (x2,y2)(x_2,y_2)(x2​,y2​) is (x1−x2)2+(y1−y2)2\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}(x1​−x2​)2+(y1​−y2​)2​.
Input
The first input line has an integer nnn: the number of points.
After this, there are nnn lines that describe the points. Each line has two integers xxx and yyy. You may assume that each point is distinct.
Output
Print one integer: d2d^2d2 where ddd is the minimum Euclidean distance (this ensures that the result is an integer).
Constraints

2≤n≤2⋅1052 \le n \le 2 \cdot 10^52≤n≤2⋅105
−109≤x,y≤109-10^9 \le x,y \le 10^9−109≤x,y≤109

Example
Input:
4
2 1
4 4
1 2
6 3

Output:
2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
struct P {
    ll x, y;
};
 
static inline ll dsq(const P &a, const P &b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
 
ll closest_pair(vector<P> &pts) {
    sort(pts.begin(), pts.end(),
         [](auto &a, auto &b) { return a.x < b.x; });
    ll best = LLONG_MAX;
    set<pair<ll, ll> > box;
    int left = 0;
    for (auto &p: pts) {
        while (left < (int) pts.size()) {
            ll dx = p.x - pts[left].x;
            if (dx * dx > best) {
                box.erase({pts[left].y, pts[left].x});
                left++;
            } else break;
        }
        ll d = ceil(sqrt((long double) best));
        auto lo = box.lower_bound({p.y - d, LLONG_MIN});
        auto hi = box.upper_bound({p.y + d, LLONG_MAX});
        for (auto it = lo; it != hi; ++it) {
            P q{it->second, it->first};
            best = min(best, dsq(p, q));
        }
        box.insert({p.y, p.x});
    }
    return best;
}
 
ll max_pair(vector<P> &pts) {
    if (pts.size() < 2) return 0;
    sort(pts.begin(), pts.end(),
         [](auto &a, auto &b) {
             return a.x < b.x || (a.x == b.x && a.y < b.y);
         });
    vector<P> H;
    for (auto &p: pts) {
        while (H.size() >= 2) {
            auto &a = H[H.size() - 2];
            auto &b = H.back();
            if ((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x) <= 0)
                H.pop_back();
            else break;
        }
        H.push_back(p);
    }
    for (int i = (int) pts.size() - 2, t = H.size() + 1; i >= 0; --i) {
        auto &p = pts[i];
        while ((int) H.size() >= t) {
            auto &a = H[H.size() - 2];
            auto &b = H.back();
            if ((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x) <= 0)
                H.pop_back();
            else break;
        }
        H.push_back(p);
    }
    H.pop_back();
    int m = H.size();
    if (m < 2) return 0;
    ll ans = 0;
    int j = 1;
    for (int i = 0; i < m; ++i) {
        int ni = (i + 1) % m;
        while (true) {
            int nj = (j + 1) % m;
            ll cross = (H[ni].x - H[i].x) * (H[nj].y - H[j].y)
                       - (H[ni].y - H[i].y) * (H[nj].x - H[j].x);
            if (cross > 0) j = nj;
            else break;
        }
        ans = max(ans, dsq(H[i], H[j]));
        ans = max(ans, dsq(H[ni], H[j]));
    }
    return ans;
}
 
int main() {
    PRE();
    int n;
    cin >> n;
    vector<P> pts(n);
    for (int i = 0; i < n; i++)
        cin >> pts[i].x >> pts[i].y;
    auto a = pts;
    auto b = pts;
    ll mn = closest_pair(a);
    ll mx = max_pair(b);
    cout << mn;
}