/* problem statement text */
/*
CSES - Convex Hull

Time limit: 1.00 s
Memory limit: 512 MB

Given a set of nnn points in the two-dimensional plane, your task is to determine the convex hull of the points.
Input
The first input line has an integer nnn: the number of points.
After this, there are nnn lines that describe the points. Each line has two integers xxx and yyy: the coordinates of a point.
You may assume that each point is distinct, and the area of the hull is positive.
Output
First print an integer kkk: the number of points in the convex hull.
After this, print kkk lines that describe the points. You can print the points in any order. Print all points that lie on the convex hull.
Constraints

3≤n≤2⋅1053 \le n \le 2 \cdot 10^53≤n≤2⋅105
−109≤x,y≤109-10^9 \le x, y \le 10^9−109≤x,y≤109

Example
Input:
6
2 1
2 5
3 3
4 3
4 4
6 3

Output:
4
2 1
2 5
4 4
6 3
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
 
using T = long double;
using pt = complex<T>;
#define X real()
#define Y imag()
const T EPS = 1e-9;
 
T dot(pt a, pt b) { return (conj(a)*b).X; }
T cross(pt a, pt b) { return (conj(a)*b).Y; }
T cross(pt o, pt a, pt b) { return cross(a-o, b-o); }
bool cmp(pt a, pt b) { return make_pair(a.X, a.Y) < make_pair(b.X, b.Y); }
 
vector<pt> hull(vector<pt> pts) {
    int n = pts.size();
    if (n <= 1) return pts;
    sort(pts.begin(), pts.end(), cmp);
    pts.erase(unique(pts.begin(), pts.end(), [](const pt &a, const pt &b){
        return fabs(a.X - b.X) < EPS && fabs(a.Y - b.Y) < EPS;
    }), pts.end());
    n = pts.size();
    if (n <= 1) return pts;
 
    vector<pt> h;
    for (int i = 0; i < n; ++i) {
        while ((int)h.size() >= 2 && cross(h[h.size()-2], h[h.size()-1], pts[i]) < -EPS) // strict < to keep collinear
            h.pop_back();
        h.push_back(pts[i]);
    }
    int lower_size = h.size();
    for (int i = n-2; i >= 0; --i) {
        while ((int)h.size() >= lower_size+1 && cross(h[h.size()-2], h[h.size()-1], pts[i]) < -EPS)
            h.pop_back();
        h.push_back(pts[i]);
    }
    if (!h.empty()) h.pop_back();
    return h;
}
// 0: outside, 1: inside, 2: touch
int in_poly(const vector<pt>& h, pt p) {
    int n = h.size();
    if (n == 0) return 0;
    if (n == 1) return abs(h[0]-p) < EPS ? 2 : 0;
    if (n == 2) return abs(cross(h[0], h[1], p)) < EPS && dot(p-h[0], p-h[1]) <= EPS ? 2 : 0;
 
    T c1 = cross(h[0], h[1], p), c2 = cross(h[0], h[n-1], p);
    if (c1 < -EPS || c2 > EPS) return 0;
    if (abs(c1) < EPS) return dot(p-h[0], p-h[1]) <= EPS ? 2 : 0;
    if (abs(c2) < EPS) return dot(p-h[0], p-h[n-1]) <= EPS ? 2 : 0;
 
    int l = 1, r = n-2, idx = -1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (cross(h[0], h[mid], p) >= -EPS) idx = mid, l = mid+1;
        else r = mid-1;
    }
    T v = cross(h[idx], h[idx+1], p);
    return v < -EPS ? 0 : (v < EPS ? 2 : 1);
}
T orient(pt a, pt b, pt c){ return cross(b - a, c - a); }
bool inDisk(pt a, pt b, pt p){ return fabs(dot(a-p, b-p)) <= EPS; }
bool onSegment(pt a, pt b, pt c){ return fabs(orient(a,b,c)) <=EPS && inDisk(a,b,c); }
 
int main() {
    PRE();
    int n;cin >> n;
    vector<pt> p(n);
    for (int i = 0;i < n;i++) {
        int x , y; cin >> x >> y;
        p[i] = pt(x , y);
    }
    auto res = hull(p);
    cout << res.size() << '\n';
    for (auto &val : res)
        cout << (int)val.X << " " << (int)val.Y << '\n';
}