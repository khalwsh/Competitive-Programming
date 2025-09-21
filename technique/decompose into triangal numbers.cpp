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

ll work(ll x) { return x * (x + 1) >> 1; }

bool check(ll x) {
    ll p = sqrt(x * 2);
    if (work(p) == x) return 1;
    return 0;
}

int main() {
    PRE();
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (check(n)) {
            cout << 1 << '\n';
        } else {
            int ans = 3;
            ll x, m;
            x = m = 2e6;
            for (ll i = 1; i <= m && work(i) <= n; i++) {
                while (work(i) + work(x) > n) x--;
                if (work(i) + work(x) == n) {
                    ans = 2;
                    break;
                }
            }
            cout << ans << '\n';
        }
    }
}
