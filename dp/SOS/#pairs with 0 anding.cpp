const int mod = 1e9 + 7;
const int N = 20;
// adding subset to superset , dp 1 base
void forward1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}
// undo subset to super set , dp 1 base
void backword1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)];
        }
    }
}
vector<ll> dp(1 << N);
int main() {
    PRE();
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        vector<int>v;
        for (int i = 0;i < n;i++) {
            int x;cin >> x;
            dp[x]++;
            v.emplace_back(x);
        }
        forward1(dp , 20);
        ll res = 0;
        for (auto &val : v) {
            res += dp[((1 << N) - 1) & ~val];
        }
        cout << res << '\n';
        backword1(dp , 20);
        for (auto &val : v) dp[val]--;
    }
}