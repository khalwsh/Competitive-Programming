
using T = long double;
using pt = complex<T>;
#define X real()
#define Y imag()
const T EPS = 1e-9;

T dot(pt a, pt b) { return (conj(a)*b).X; }
T cross(pt a, pt b) { return (conj(a)*b).Y; }
T cross(pt o, pt a, pt b) { return cross(a-o, b-o); }
bool cmp(pt a, pt b) { return make_pair(a.X, a.Y) < make_pair(b.X, b.Y); }

vector<pt> hull(vector<pt>& p) {
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    vector<pt> h(2*n);
    sort(p.begin(), p.end(), cmp);
    for (int i=0; i<n; ++i) {
        while (k>=2 && cross(h[k-2], h[k-1], p[i]) <= EPS) k--;
        h[k++] = p[i];
    }
    for (int i=n-2, t=k+1; i>=0; i--) {
        while (k>=t && cross(h[k-2], h[k-1], p[i]) <= EPS) k--;
        h[k++] = p[i];
    }
    h.resize(k-1);
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