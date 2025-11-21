
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