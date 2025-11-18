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

int main() {
    PRE();
    ll n;cin >> n;
    ll res = 0;
    for (int i = 0; i < 60; i++) {
        ll bit = 1LL << i;
        ll cycle = bit << 1;

        ll full = n / cycle;
        ll rem = n % cycle;

        res += full * bit;
        res += max(0LL, rem - bit + 1);
    }
    cout << res << '\n';
}
