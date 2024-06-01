ll dp[3005];
int n,m;
int main() {
    cin >> n >> m;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
        dp[0] = (dp[0] << 1) % mod;
    int inv = fast_power(2ll , mod - 2 , mod);
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        for (int j = m; j >= x; --j)
            dp[j] = (dp[j] + 1ll * dp[j - x] * inv) % mod;
    }
    cout << dp[m] << line;
}