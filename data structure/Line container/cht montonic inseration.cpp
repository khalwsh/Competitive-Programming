// Convex Hull Trick (Monotonic Insertion & Queries)
// -----------------------------------------------------
// Usage notes:
// 1. Lines must be added in strictly monotonic order of slope k (either all increasing or all decreasing).
// 2. For arbitrary x queries, use get(x), which is O(log n) via binary search.
// 3. For amortized O(1) queries when x values follow a monotonic pattern matching your slope order:
//    • If slopes k are added in increasing order, x queries must be non-decreasing for get_mono(x).
//    • If slopes k are added in decreasing order, x queries must be non-increasing for get_mono(x).
//    Use get_mono(x) to advance (or retreat) the pointer in O(1) amortized time.

#include <bits/stdc++.h>
using namespace std;

typedef int ftype;
typedef complex<ftype> point;
#define x real
#define y imag

// Dot product: a.x*b.x + a.y*b.y
ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

// 2D cross product (perp dot): a.x*b.y - a.y*b.x
ftype cross(point a, point b) {
    return (conj(a) * b).y();
}

static vector<point> hull, vecs;
static size_t mono_ptr = 0; // pointer for monotonic queries

// Add a line y = k*x + b to the hull.
// Slopes (k) must be monotonic on insertion.
void add_line(ftype k, ftype b) {
    point nw = {k, b};
    // Remove last while new line breaks convexity
    while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if (!hull.empty()) {
        // Store perpendicular vector (rotated +90°) for binary search
        vecs.push_back(point(0,1) * (nw - hull.back()));
    }
    hull.push_back(nw);
}

// Query maximum at x: O(log n)
// Use for arbitrary (non-monotonic) x queries.
ftype get(ftype x) {
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query,
        [](point a, point b) {
            return cross(a, b) > 0;
        }
    );
    size_t idx = it - vecs.begin();
    return dot(query, hull[idx]);
}

// Query maximum at x: O(1) amortized
// Requires that x queries follow the same monotonic direction as slope insertion.
ftype get_mono(ftype x) {
    // Advance or retreat pointer based on hull size
    while (mono_ptr + 1 < hull.size() &&
           dot(point(x,1), hull[mono_ptr]) <= dot(point(x,1), hull[mono_ptr+1])) {
        mono_ptr++;
    }
    while (mono_ptr > 0 &&
           dot(point(x,1), hull[mono_ptr]) <= dot(point(x,1), hull[mono_ptr-1])) {
        mono_ptr--;
    }
    return dot(point(x,1), hull[mono_ptr]);
}