#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
struct Basis {
    const static int BITs = 60;
    ll basis[BITs + 1]{};
    int comp_sz = 0;

    void insert(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }

    ll get(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (msk >> i & 1) continue;
            msk ^= basis[i];
        }
        return msk;
    }
};
int main(){
    PRE();
    Basis bs;
    int n;cin >> n;
    vector<ll>a(n);
    ll XOR = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        XOR ^= a[i];
    }
    ll ans = XOR;
    for (int i = 0; i < n; ++i) {
        bs.insert(a[i] & ~XOR);
    }
    cout << ans + 2 * bs.get(0);
}
