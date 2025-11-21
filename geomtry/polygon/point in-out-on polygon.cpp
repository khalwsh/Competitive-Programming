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

