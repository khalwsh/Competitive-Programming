// m colors n elements
const int mod = 1e9 + 7;
 
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += binpow(m, __gcd(i, n));
        res %= mod;
    }
    cout << res * binpow(n, mod - 2) % mod;
}
