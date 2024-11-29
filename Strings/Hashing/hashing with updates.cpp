#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll HASH = 257, MOD = 1e9 + 7;

const int md = 1e9+7;
int B = 73; //Sheldon prime (lol)
const int mxN = 1e6+6;
ll pB[mxN];
struct {
    ll bit[mxN] = {0};

    void update(int k, ll x) {
        x %= md;
        if (x < md) x += md;
        for (; k < mxN; k += k&-k) {
            (bit[k] += x) %= md;
        }
    }

    ll query(int k) {
        ll s = 0;
        for (; k > 0; k -= k&-k)
            (s += bit[k]) %= md;
        return s;
    }
} pre, suf;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    B = uniform_int_distribution<int>(73, 7337)(rng);
    int n, t; cin>>n>>t;

    string s; cin>>s;
    pB[0] = 1;
    for (int i = 1; i < mxN; i++)
        pB[i] = pB[i-1] * B % md;

    for (int i = 0; i < n; i++) {
        pre.update(i+1, (s[i]-'a'+1) * pB[i]);
        suf.update(i+1, (s[i]-'a'+1) * pB[n-i-1]);
    }
    while (t--) {
        int ch; cin>>ch;
        if (ch == 1) {
            int k; char x;
            cin>>k>>x; k--;
            pre.update(k+1, -(s[k]-'a'+1) * pB[k]);
            pre.update(k+1, (x-'a'+1) * pB[k]);
            suf.update(k+1, -(s[k]-'a'+1) * pB[n-k-1]);
            suf.update(k+1, (x-'a'+1) * pB[n-k-1]);
            s[k] = x;
        }
        else {
            int x, y; cin>>x>>y;
            ll h1 = (pre.query((x+y)/2) - pre.query(x-1) + md) % md;
            ll m1 = pB[x-1];
            ll h2 = (suf.query(y) - suf.query((x+y-1)/2) + md) % md;
            ll m2 = pB[n-y];
            cout << (h1 * m2 % md == h2 * m1 % md ? "YES" : "NO" ) << '\n';
        }
    }
}