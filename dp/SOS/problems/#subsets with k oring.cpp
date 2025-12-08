const int mod = 1e9 + 7;
const int N = 20;
// adding subset to superset , dp 1 base
void forward1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)] , dp[j] %= mod;
        }
    }
}
// undo subset to super set , dp 1 base
void backword1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)] , dp[j] = (dp[j] + mod) % mod;
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
    int m;
    int n;cin >> n >> m;
    for (int i = 0;i < n;i++) {
        string s;cin >> s;
        int x = 0;
        reverse(s.begin() , s.end());
        for (int j = 0;j < m;j++) {
            if (s[j] == '1')
                x |= 1 << j;
        }
        dp[x]++;
    }
    forward1(dp , N);
    for (int i = 0;i < 1 << N;i++) {
        dp2[i] = (fp(2 , dp[i]) - 1 + mod) % mod;
    }
    backword1(dp2 , N);
    string s;cin >> s;
    int x = 0;
    reverse(s.begin() , s.end());
    for (int j = 0;j < m;j++) {
        if (s[j] == '1')
            x |= 1 << j;
    }
    cout << dp2[x] << '\n';
}