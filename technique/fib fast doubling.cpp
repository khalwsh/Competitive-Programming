pair<ll, ll> fib_fast_doubling(ll n, ll mod) {
    if(n == 0)
        return {0, 1};
    auto p = fib_fast_doubling(n >> 1, mod);
    ll a = p.first;
    ll b = p.second;
    ll c = (a * ((2 * b + mod - a) % mod)) % mod;
    ll d = ((a * a) % mod + (b * b) % mod) % mod;
    if(n & 1)
        return {d, (c + d) % mod};
    else
        return {c, d};
}

ll fib(ll n, ll mod) {
    return fib_fast_doubling(n, mod).first;
}