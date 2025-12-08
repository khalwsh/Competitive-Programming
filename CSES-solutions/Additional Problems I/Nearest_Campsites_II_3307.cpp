/* problem statement text */
/*
CSES - Nearest Campsites II

Time limit: 1.00 s
Memory limit: 512 MB

A campground is represented as a grid where each square can contain a campsite that is either reserved or free. The distance between two squares (x1,y1)(x_1, y_1)(x1​,y1​) and (x2,y2)(x_2, y_2)(x2​,y2​) is the Manhattan distance ∣x1−x2∣+∣y1−y2∣|x_1 - x_2| + |y_1 - y_2|∣x1​−x2​∣+∣y1​−y2​∣.
Your task is to find the distance from each free campsite to the nearest reserved campsite.
Input
The first line has two integers nnn and mmm:
the number of reserved and free campsites.
The next nnn lines describe the locations of the reserved campsites. Each line has two integers xxx and yyy.
The next mmm lines describe the locations of the free campsites. Each line has two integers xxx and yyy.
You can assume that each square contains at most one campsite.
Output
Print mmm integers: the distances from each free campsite to the nearest reserved campsite, in the input order.
Constraints

1≤n,m≤1051 \le n, m \le 10^51≤n,m≤105
1≤x,y≤1061 \le x, y \le 10^61≤x,y≤106

Example
Input:
4 2
1 1
5 2
2 6
4 7
1 3
7 5

Output:
2 5

Explanation: The following figure shows the map of the campground:

The distance from the first free campsite (on the left) to the nearest reserved campsite is 222, and the distance from the second free campsite (on the right) to the nearest reserved campsite is 555.
*/
#include <bits/stdc++.h>
 
#include <random>
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
// --- KD-TREE TEMPLATE START ---
 
struct P {
    ll x, y;
    int id;
 
    ll dist(const P& b) const {
        // 1. MANHATTAN (Current)
        return abs(x - b.x) + abs(y - b.y);
 
        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
    }
    bool operator<(P &z) {
        return x < z.x || (x == z.x && y < z.y);
    }
    bool operator==(P &z) {
        return x == z.x && y == z.y;
    }
};
const int INF = 1e9;
struct Node {
    P p;
    int l = -1;
    int r = -1;
 
    ll x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
 
    Node() {}
    Node(P pt) : p(pt) {
        x0 = x1 = pt.x;
        y0 = y1 = pt.y;
    }
 
    ll boxDist(const P& q) const {
        ll X = max(x0, min(x1, q.x));
        ll Y = max(y0, min(y1, q.y));
 
        // 1. MANHATTAN (Current)
        return abs(q.x - X) + abs(q.y - Y);
 
        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (q.x - X)*(q.x - X) + (q.y - Y)*(q.y - Y);
    }
};
 
// Global comparators for nth_element
bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }
 
struct KDTree {
    vector<Node> pool;
    int root = -1;
    ll min_d;
    P best_p;
    int q_id;
 
    int build(vector<P> &pts, int L, int R) {
        if (L >= R) return -1;
 
        // 1. Calculate Bounding Box of current points to decide split axis
        ll min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
        for(int i=L; i<R; ++i) {
            if(pts[i].x < min_x) min_x = pts[i].x;
            if(pts[i].x > max_x) max_x = pts[i].x;
            if(pts[i].y < min_y) min_y = pts[i].y;
            if(pts[i].y > max_y) max_y = pts[i].y;
        }
 
        // 2. Adaptive Split: Split on the widest dimension
        // This creates square-like bounding boxes which are better for pruning
        bool divX = (ll)(max_x - min_x) >= (ll)(max_y - min_y);
 
        int mid = (L + R) / 2;
        nth_element(pts.begin() + L, pts.begin() + mid, pts.begin() + R, divX ? on_x : on_y);
 
        int idx = pool.size();
        pool.push_back(Node(pts[mid]));
 
        // Set the bounding box exactly to what we computed
        pool[idx].x0 = min_x; pool[idx].x1 = max_x;
        pool[idx].y0 = min_y; pool[idx].y1 = max_y;
 
        // 3. Recurse
        pool[idx].l = build(pts, L, mid);
        pool[idx].r = build(pts, mid + 1, R);
 
        return idx;
    }
 
    void search(int node_idx, const P& q) {
        if (node_idx == -1 || pool[node_idx].boxDist(q) >= min_d) return;
 
        ll d = pool[node_idx].p.dist(q);
 
        // Check condition: strictly better dist AND not the point itself
        if (d < min_d && pool[node_idx].p.id != q_id) {
            min_d = d;
            best_p = pool[node_idx].p;
        }
 
        if (min_d == 0) return;
 
        int L = pool[node_idx].l;
        int R = pool[node_idx].r;
 
        ll dL = (L != -1) ? pool[L].boxDist(q) : INF;
        ll dR = (R != -1) ? pool[R].boxDist(q) : INF;
 
        // Visit closer box first
        if (dL < dR) { search(L, q); search(R, q); }
        else         { search(R, q); search(L, q); }
    }
 
    KDTree(vector<P>& pts) {
        pool.reserve(pts.size());
        root = build(pts, 0, pts.size());
    }
 
    // Returns {distance, Point}
    // Usage: nearest(q) -> any neighbor. nearest(q, q.id) -> neighbor != q
    pair<ll, P> nearest(P q, int ignore_id = -1) {
        min_d = INF;
        q_id = ignore_id;
        best_p = P();
        search(root, q);
        return {min_d, best_p};
    }
    ll find_closest_pair(const vector<P>& pts) {
        min_d = INF;
        for (const auto& p : pts) {
            q_id = p.id; // Ignore self
            search(root, p);
        }
        return min_d;
    }
};
 
 
 
int main() {
    PRE();
    int n , q; cin >> n >> q;
    vector<P> a(n) , b(q);
    for (auto &val : a) cin >> val.x >> val.y;
    sort(a.begin() , a.end());
    a.erase(unique(a.begin() , a.end()) , a.end());
    shuffle(a.begin() , a.end(), std::mt19937(std::random_device()()));
    KDTree kd(a);
    for (auto &val : b) {
        cin >> val.x >> val.y;
        cout << kd.nearest(val , -1).first << " ";
    }
}