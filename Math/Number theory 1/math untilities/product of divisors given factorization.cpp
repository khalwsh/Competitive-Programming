const ll MOD = 1000000007LL;
const ll MOD1 = 1000000006LL;

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

ll productDivisors(const vector<pair<ll,ll>>& orig_factors) {
    vector<pair<ll,ll>> factors = orig_factors;
    ll num1 = 1;
    bool halvedOne = false;
    for (auto &p : factors) {
        ll k = p.second;
        if (!halvedOne && (k % 2 == 1)) {
            num1 = (num1 * (( (k + 1) / 2 ) % MOD1)) % MOD1;
            halvedOne = true;
        } else {
            num1 = (num1 * ((k + 1) % MOD1)) % MOD1;
        }
    }
    if (!halvedOne) {
        for (auto &p : factors) p.second /= 2;
    }
    ll number = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        number = ( (__int128)number * modpow(x, k, MOD) ) % MOD;
    }
    ll prod = modpow(number, num1, MOD);
    return prod;
}
