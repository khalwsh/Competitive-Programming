ll a[N],dp[N];
int main() {
    khaled
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        dp[0] += 1;
        for (int j = k; j >= a[i]; j--)
            dp[j] = (dp[j] + dp[j - a[i]]) % mod;
        ans = (ans + dp[k]) % mod;
    }
    cout << ans << endl;
    return 0;
}