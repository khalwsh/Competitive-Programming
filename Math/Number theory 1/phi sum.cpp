const int  SQ = 1000000 , mod = 1e9 + 7;
ll pre[SQ+1];
unordered_map<ll,ll> dp;

void build() {
    vector<int> phi(SQ+1);
    for (int i = 1; i <= SQ; i++) phi[i] = i;
    for (int p = 2; p <= SQ; p++) {
        if (phi[p] == p) {
            for (int j = p; j <= SQ; j += p)
                phi[j] -= phi[j] / p;
        }
    }
    pre[0] = 0;
    for (int i = 1; i <= SQ; i++)
        pre[i] = pre[i-1] + phi[i];

    dp.reserve(2 * SQ);
}
ll S(ll n) {
    if (n <= SQ)
        return pre[n];
    auto it = dp.find(n);
    if (it != dp.end())
        return it->second;

    ll ans = n * (n + 1) / 2 % mod;
    ll i = 2;
    while (i <= n) {
        ll q    = n / i;
        ll last = n / q;
        ans    -= (last - i + 1) * S(q);
        ans = (ans % mod + mod) % mod;
        i       = last + 1;
    }
    return dp[n] = ans;
}
