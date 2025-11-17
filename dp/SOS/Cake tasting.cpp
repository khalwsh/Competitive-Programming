#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
// given n shops , a[i] number of distinct cakes in the ith mask
// restore the cakes in each shops to make data consistent
int main() {
    int n; cin >> n;
    int ALL = (1<<n)-1;
    vector<ll> A(1<<n, 0);
    for(int mask=1; mask<=ALL; ++mask) cin >> A[mask];

    ll total = A[ALL];
    vector<ll> h(1<<n);
    for(int mask=0; mask<=ALL; ++mask) {
        int comp = ALL ^ mask;
        ll aval = A[comp];
        h[mask] = total - aval;
    }
    vector<ll> b = h;
    for(int i=0;i<n;++i){
        for(int mask=0; mask<=ALL; ++mask){
            if(mask & (1<<i)) b[mask] -= b[mask ^ (1<<i)];
        }
    }
    for(int mask=1; mask<=ALL; ++mask){
        if(b[mask] < 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    vector<vector<int>> shop(n);
    int nextId = 1;
    for(int mask=1; mask<=ALL; ++mask){
        for(ll cnt=0; cnt<b[mask]; ++cnt){
            for(int i=0;i<n;++i) if(mask & (1<<i)) shop[i].push_back(nextId);
            ++nextId;
        }
    }
    for(int i=0;i<n;++i){
        cout << shop[i].size();
        for(int x: shop[i]) cout << ' ' << x;
        cout << '\n';
    }
}