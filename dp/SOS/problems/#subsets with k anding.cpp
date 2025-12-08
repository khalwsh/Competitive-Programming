const int mod = 1e9 + 7;
const int N = 20;
// adding superset to subset , dp 1 base
void forward2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j] , dp[j ^ (1 << i)] %= mod;
        }
    }
}
// undo superset to subset
void backword2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j] , dp[j ^ (1 << i)] = (dp[j ^ (1 << i)] + mod) % mod;
        }
    }
}
ll fp(ll a , ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
vector<ll> dp(1 << N);
vector<ll> dp2(1 << N);
int main() {
    PRE();
    int n;cin >> n;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        dp[x]++;
    }
    forward2(dp , N);
    for (int i = 0;i < 1 << N;i++) {
        dp2[i] = (fp(2 , dp[i]) - 1 + mod) % mod;
    }
    backword2(dp2 , N);
    for (int i = 0;i <= n;i++)
        cout << dp2[i] << ' ';
}