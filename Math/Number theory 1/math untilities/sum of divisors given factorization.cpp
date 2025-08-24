const ll MOD = 1000000007LL;

ll modpow(ll a, ll b, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = ( (__int128)res * a ) % mod;
        a = ( (__int128)a * a ) % mod;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

ll sumDivisors(const vector<pair<ll,ll>>& factors) {
    ll ans = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        if (x == 1) {
            ans = (ans * ((k + 1) % MOD)) % MOD;
        } else {
            ll numerator = (modpow(x, k + 1, MOD) - 1 + MOD) % MOD;
            ll denom_inv = modinv((x - 1 + MOD) % MOD, MOD);
            ll term = ( (__int128)numerator * denom_inv ) % MOD;
            ans = (ans * term) % MOD;
        }
    }
    return ans;
}