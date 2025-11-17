#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
// adding subset to superset , dp 1 base
void forward1(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}
// adding superset to subset , dp 1 base
void forward2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j];
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
// undo superset to subset
void backword2(vector<ll> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = dp.size() - 1;j > 0;j--) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j];
        }
    }
}
const int N = 20;
vector<ll>dp(1 << N);
int main() {
    PRE();
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        for (auto &val : dp) val = 0;
        vector<int>v(n);
        for (auto &val : v) cin >> val , dp[val]++;
        forward1(dp , N);
        ll res = 0;
        map<int ,int>freq;
        for (auto &val : v) {
            res += dp[val] - freq[val]++;
        }
        cout << res - n << '\n';
    }
}