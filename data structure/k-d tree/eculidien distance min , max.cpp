struct P { ll x,y; };

static inline ll dsq(const P &a, const P &b){
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}

ll closest_pair(vector<P>& pts) {
    sort(pts.begin(), pts.end(),
         [](auto &a, auto &b){ return a.x < b.x; });
    ll best = LLONG_MAX;
    set<pair<ll,ll>> box;
    int left = 0;
    for (auto &p : pts) {
        while (left < (int)pts.size()) {
            ll dx = p.x - pts[left].x;
            if (dx*dx > best) {
                box.erase({pts[left].y, pts[left].x});
                left++;
            } else break;
        }
        ll d = ceil(sqrt((long double)best));
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

ll max_pair(vector<P>& pts) {
    if (pts.size() < 2) return 0;
    sort(pts.begin(), pts.end(),
         [](auto &a, auto &b){
            return a.x < b.x || (a.x == b.x && a.y < b.y);
         });
    vector<P> H;
    for (auto &p : pts) {
        while (H.size() >= 2) {
            auto &a = H[H.size()-2];
            auto &b = H.back();
            if ((b.x-a.x)*(p.y-a.y) - (b.y-a.y)*(p.x-a.x) <= 0)
                H.pop_back();
            else break;
        }
        H.push_back(p);
    }
    for (int i = (int)pts.size()-2, t = H.size()+1; i >= 0; --i) {
        auto &p = pts[i];
        while ((int)H.size() >= t) {
            auto &a = H[H.size()-2];
            auto &b = H.back();
            if ((b.x-a.x)*(p.y-a.y) - (b.y-a.y)*(p.x-a.x) <= 0)
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
        int ni = (i+1)%m;
        while (true) {
            int nj = (j+1)%m;
            ll cross = (H[ni].x-H[i].x)*(H[nj].y-H[j].y)
                     - (H[ni].y-H[i].y)*(H[nj].x-H[j].x);
            if (cross > 0) j = nj;
            else break;
        }
        ans = max(ans, dsq(H[i], H[j]));
        ans = max(ans, dsq(H[ni], H[j]));
    }
    return ans;
}
