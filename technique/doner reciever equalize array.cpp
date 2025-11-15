// you have array a up to 22 and you need all its values be the same , do it with minimal moves
// in one move value at position x can be decreased by z and value at position y can be increased with z
vector<array<ll , 3>> calc(vector<ll>&a) {
    ll sum = 0;
    ll n = a.size();
    vector<ll> dp, subsum, dprev;
    vector<ll> x, y, z;
    for (ll i = 0; i < n; i++) {
        sum += a[i];
    }
    if (sum % n != 0) {
        // no sol
        return {{-1 , -1 , -1}};
    }
    ll avg = sum / n;
    dp.resize(1LL << n);
    subsum.resize(1LL << n);
    dprev.resize(1LL << n);
    dp[0] = 0;
    subsum[0] = 0;
    dprev[0] = -1;
    for (ll b = 1; b < 1 << n; b++) {
        dp[b] = n+1;
        dprev[b] = -1;

        subsum[b] = 0;
        for (ll i = 0; i < n; i++) {
            if (b & (1LL << i)) subsum[b] += (a[i] - avg);
        }
        ll item = ((subsum[b] == 0) ? 0 : +1);
        for (ll i = 0; i < n; i++) {
            if (b & (1LL << i)) {
                ll maybe = dp[b - (1LL << i)] + item;
                if (dp[b] > maybe) {
                    dp[b] = maybe;
                    dprev[b] = i;
                }
            }
        }
    }
    ll cb = (1LL << n) - 1;
    while (cb) {
        vector<pair<ll, ll> > v;
        while (true) {
            ll vi = dprev[cb];
            v.push_back({-a[vi], vi}); // a[i] in decreasing order
            cb -= (1LL << vi);
            if (subsum[cb] == 0) break;
        }
        sort(v.begin(), v.end());
        ll carry = a[v[0].second] - avg;
        for (ll i = 1; i < v.size(); i++) {
            x.push_back(v[i-1].second);
            y.push_back(v[i-0].second);
            z.push_back(carry);
            carry += (a[v[i].second] - avg);
        }
    }
    vector<array<ll , 3>> res;
    for (ll i = 0; i < z.size(); i++) {
        res.emplace_back(array<ll , 3> {x[i] + 1 , (y[i] + 1) , z[i]});
    }
    return res;
}