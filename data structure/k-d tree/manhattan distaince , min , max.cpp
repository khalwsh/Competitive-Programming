const int N = 1e5 + 10;
ll n , x[N] ,y[N];

ll get_max() {
    ll mn1 = LLONG_MAX, mx1 = LLONG_MIN;
    ll mn2 = LLONG_MAX, mx2 = LLONG_MIN;
    // transform:  u = x + y,   v = x - y;
    for (int i = 0; i < n; i++) {
        ll u = x[i] + y[i];
        ll v = x[i] - y[i];
        mn1 = min(mn1, u);
        mx1 = max(mx1, u);
        mn2 = min(mn2, v);
        mx2 = max(mx2, v);
    }
    return max(mx1 - mn1, mx2 - mn2);
}

struct P { ll u, v; };
ll closest_Linf(vector<P>& a, int l, int r) {
    int m = (l + r) >> 1;
    ll mid_u = a[m].u;
    if (r - l <= 3) {
        ll d = LLONG_MAX;
        for (int i = l; i <= r; ++i)
            for (int j = i+1; j <= r; ++j)
                d = min(d, max( llabs(a[i].u - a[j].u), llabs(a[i].v - a[j].v) ));
        sort(a.begin()+l, a.begin()+r+1, [](auto& A, auto& B){ return A.v < B.v; });
        return d;
    }
    ll d = min(
        closest_Linf(a, l, m),
        closest_Linf(a, m+1, r)
    );
    inplace_merge(a.begin()+l, a.begin()+m+1, a.begin()+r+1,
                  [](auto& A, auto& B){ return A.v < B.v; });
    vector<P> strip;
    for (int i = l; i <= r; ++i)
        if ( llabs(a[i].u - mid_u) < d )
            strip.push_back(a[i]);
    for (int i = 0; i < (int)strip.size(); ++i) {
        for (int j = i+1; j < (int)strip.size() && strip[j].v - strip[i].v < d; ++j) {
            d = min(d, max( llabs(strip[i].u - strip[j].u),
                            llabs(strip[i].v - strip[j].v) ));
        }
    }
    return d;
}

ll get_min() {
    vector<P> a(n);
    for (int i = 0; i < n; i++) {
        a[i].u = x[i] + y[i];
        a[i].v = x[i] - y[i];
    }
    sort(a.begin(), a.end(), [](auto& A, auto& B){
        return A.u < B.u;
    });
    return closest_Linf(a, 0, n-1);
}