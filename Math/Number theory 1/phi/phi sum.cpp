const ll mod = 1e9 + 7, inv = (1e9 + 8) / 2;
 
const int N = 1e7;
ll phi[N + 1], pref[N + 1];
void buildPhi(ll n) {
    pref[1] = 1;
    for (ll i = 0; i <= n; i++) phi[i] = i;
    for (ll i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (ll j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
        pref[i] = pref[i - 1] + phi[i];
        if(pref[i] >= mod) pref[i] -= mod;
    }
}
 
unordered_map<ll, ll> dp;
ll sum(ll n) {
    if(n < N) return pref[n];
    if(dp.count(n)) return dp[n];
    ll at = 1, value = n;
    ll ans = (n%mod) * ((n + 1) % mod) % mod * inv % mod;
    while (at <= value) {
        ll t = value / at;
        ll nxt = value / t + 1;
        ll cnt = nxt - at;
        cnt %= mod;
        if(t != n) ans -= sum(t) * cnt % mod;
        if(ans < 0) ans += mod;
        at = nxt;
    }
    return dp[n] = ans;
}
 