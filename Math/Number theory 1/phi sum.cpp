const int mod = 1e9 + 7;
int modProd(ll a, ll b) {
    if (a < 0)
        a += mod;
    if (b < 0)
        b += mod;
    a %= mod;
    b %= mod;
    a *= b;
    if (a >= mod)
        a %= mod;
    return a;

}

int modPow(int a, ll b) {
    int result = 1;
    while (b) {
        if (b & 1)
            result = modProd(result, a);
        a = modProd(a, a);
        b >>= 1;
    }
    return result;
}


int modInverse(int a) {
    return modPow(a, mod - 2);
}


int modDiv(int a, int b) {
    return modProd(a, modInverse(b));
}
ll phi(ll d) {
    ll res = d;
    for (ll p = 2; p * p <= d; p++) {
        if (d % p == 0) {
            while (d % p == 0) d /= p;
            res -= res / p;
        }
    }
    if (d > 1) res -= res / d;
    return res % mod;
}

ll sum(ll n) {
    if (n == 1)return 1;
    return modDiv(modProd(n, phi(n)), 2);
}