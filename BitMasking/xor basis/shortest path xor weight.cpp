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
const int N = 1e5 + 10;
struct Basis {
    static const int BITs = 30;
    int basis[BITs + 1]{};
    int comp_sz = 0;
    void insert(int msk) {
        for (int i = BITs; i >= 0;i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }
    ll min_xor(ll x){
        for(int i = BITs - 1; i >= 0; --i){
            if( (x ^ basis[i]) < x) x ^= basis[i];
        }
        return x;
    }
}bs;
int n , m;
vector<pair<int ,int>>adj[N];
int a[N];
bool vis[N];
void dfs(int u , int p, int val) {
    if (vis[u]) {
        bs.insert(a[u] ^ val);
        return;
    }
    vis[u] = true;
    a[u] = val;
    for(auto &[v , w] : adj[u]) if(v != p){
        dfs(v , u , val ^ w);
    }
}
int main(){
    PRE();
    cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v-- ;
        int w;cin >> w;
        adj[u].emplace_back(v, w);
        swap(u , v);
        adj[u].emplace_back(v , w);
    }
    dfs(0 , -1, 0);
    cout << bs.min_xor(a[n - 1]);
}
