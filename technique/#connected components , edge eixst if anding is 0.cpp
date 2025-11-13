#include <bits/stdc++.h>
#define pc(c) putchar(c)
#define rep(a,b,c) for (int a = (b) ; a < (c) ; ++a)
#define endl '\n'

using namespace std;
using ll = long long ;
using ai2 = array<int,2> ;

const int maxn = 5e6 + 10 ;

bool st[maxn],vis[maxn] ;
int a[maxn] ;

int lim ;
inline int lb(int x){
    return x & -x ;
};
inline void dfs(int u) {
    if (vis[u]) return  ;
    vis[u] = 1;

    if (st[u]) dfs(u ^ lim) ;
    int x = u ;
    while (x) {        
	dfs(u - lb(x)) ;
        x &= x - 1;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m ;
    while(cin >> n >> m) {
        lim = (1 << n) - 1;
        memset(vis,0,lim + 1) ;
        int res = 0 ;
        rep(i,1,m + 1) {
            cin >> a[i],st[a[i]] = 1 ;
            if (!a[i]) res = 1;
        }
        if (!res) {
            rep(i,1,m + 1) {
                if (!vis[a[i]]) {
                    dfs(a[i] ^ lim) ;
                    ++ res ;
                }
            }
        }
        cout << res << endl ;
        rep(i,1,m + 1) st[a[i]] = 0 ;
    }

    return 0;
}