const int N = 1e6 + 10;
int freq[N], cnt[N];
ll dp[N];
int main() {
    PRE();
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            cnt[i] += freq[j];
        }
    }
    for (int i = N - 1; i > 0; i--) {
        ll total = 1LL * cnt[i] * (cnt[i] - 1) / 2; // number of pairs with gcd i , if subsets you can make it 2 ^ cnt[i] - 1
        for (int j = 2 * i; j < N; j += i) {
            total -= dp[j];
        }
        dp[i] = total;
    }

    cout << dp[1] << "\n";
}
