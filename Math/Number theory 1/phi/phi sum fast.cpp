typedef __int128 i128;
inline i128 totient_sum(const ll N) {
    int v = int(std::sqrt(N));
    while (ll(v) * v < N) ++v;
    while (ll(v) * v > N) --v;
 
    std::vector<int> primes;
    std::vector<ll> s0(v + 1), s1(v + 1), l0(v + 1);
    std::vector<i128> l1(v + 1);
 
    const auto f = [&](int p, int e) -> ll {
        ll ret = p - 1;
        while (e > 1) --e, ret *= p;
        return ret;
    };
 
    const auto divide = [](ll n, ll d) -> ll { return ll(double(n) / d); };
 
    for (int i = 1; i <= v; ++i) s0[i] = i - 1, s1[i] = ll(i) * (i + 1) / 2 - 1;
    for (int i = 1; i <= v; ++i) l0[i] = N / i - 1, l1[i] = i128(N / i) * (N / i + 1) / 2 - 1;
    for (int p = 2; p <= v; ++p) {
        if (s0[p] > s0[p - 1]) {
            primes.push_back(p);
            ll q = ll(p) * p, M = N / p, t0 = s0[p - 1], t1 = s1[p - 1];
            ll t = v / p, u = std::min<ll>(v, N / q);
            for (ll i = 1; i <= t; ++i) l0[i] -= (l0[i * p] - t0), l1[i] -= (l1[i * p] - t1) * p;
            for (ll i = t + 1; i <= u; ++i) l0[i] -= (s0[divide(M, i)] - t0), l1[i] -= (s1[divide(M, i)] - t1) * p;
            for (int i = v; i >= q; --i) s0[i] -= (s0[divide(i, p)] - t0), s1[i] -= (s1[divide(i, p)] - t1) * p;
        }
    }
    for (int i = 1; i <= v; ++i) s1[i] -= s0[i];
    for (int i = 1; i <= v; ++i) l1[i] -= l0[i];
 
    for (auto it = primes.rbegin(); it != primes.rend(); ++it) {
        int p = *it;
        ll q = ll(p) * p, M = N / p, s = s1[p - 1];
        ll t = v / p, u = std::min<ll>(v, N / q);
        for (ll i = q; i <= v; ++i) s1[i] += (s1[divide(i, p)] - s) * f(p, 1);
        for (ll i = u; i > t; --i) l1[i] += (s1[divide(M, i)] - s) * f(p, 1);
        for (ll i = t; i >= 1; --i) l1[i] += (l1[i * p] - s) * f(p, 1);
    }
 
    for (int i = 1; i <= v; ++i) s1[i] += 1;
    for (int i = 1; i <= v; ++i) l1[i] += 1;
 
    const auto dfs = [&](auto &&self, ll n, unsigned beg, ll coeff) -> i128 {
        if (!coeff) return 0;
 
        i128 ret = i128(coeff) * (n > v ? l1[divide(N, n)] : s1[n]);
        for (unsigned i = beg; i < primes.size(); ++i) {
            int p = primes[i];
            ll q = ll(p) * p;
            if (q > n) break;
 
            ll nn = divide(n, q);
            for (int e = 2; nn > 0; nn = divide(nn, p), ++e)
                ret += self(self, nn, i + 1, coeff * (f(p, e) - f(p, 1) * f(p, e - 1)));
        }
 
        return ret;
    };
 
    return dfs(dfs, N, 0, 1);
}