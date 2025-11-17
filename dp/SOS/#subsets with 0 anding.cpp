const int mod = 1e9 + 7;
const int N = 20;
ll dp[1 << N];
ll fp(ll a , ll b) {
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
    int n;cin >> n;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        dp[x]++;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 1;j < (1 << N);j++) {
            if (j & (1 << i)){
                dp[j ^ (1 << i)] += dp[j];
                dp[j ^ (1 << i)] %= mod;
            }
        }
    }
    ll res = (fp(2 , n) - 1 + mod) % mod;
    for (int i = 1;i < 1 << N;i++) {
        ll sign = __builtin_popcount(i) & 1 ? 1 : -1;
        res -= sign * (fp(2 , dp[i]) - 1 + mod) % mod;
        res %= mod;
        res = (res + mod) % mod;
    }
    cout << res << '\n';
}