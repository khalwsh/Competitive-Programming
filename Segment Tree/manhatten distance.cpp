#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
int N;
const int M = 4e5 + 9;
ll treeUP[2][4 * M] , treeDW[2][4 * M];
void upd(int i , ll v , ll tree[] , int x = 0 , int l = 0 , int r = N){
    if(r - l == 1){ tree[x] = min(tree[x] , v); return; }
    int mid = (l + r) / 2;
    if(i < mid) upd(i , v , tree , 2 * x + 1 , l , mid);
    else upd(i , v , tree , 2 * x + 2 , mid , r);
    tree[x] = min(tree[2 * x + 1] , tree[2 * x + 2]);
}
ll qry(int lx , int rx , ll tree[] , int x = 0 , int l = 0 , int r = N){
    if(l >= lx && r <= rx) return tree[x];
    if(r <= lx || l >= rx) return 5e18;
    int mid = (l + r) / 2;
    return min( qry(lx , rx , tree , 2 * x + 1 , l , mid), 
                qry(lx , rx , tree , 2 * x + 2 , mid , r)
           );
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int tc; cin >> tc;
    while(tc--){
        int n , m; cin >> n >> m;
        vector<array<ll,3>> v; // {x , y , t(0 , 1)}
        vector<ll> allY;
        for(int i = 0; i < n; ++i){
            ll x , y; cin >> x >> y;
            v.push_back({x , y , 0});
            allY.emplace_back(y);
        }
        for(int i = 0; i < m; ++i){
            ll x , y; cin >> x >> y;
            v.push_back({x , y , 1});
            allY.emplace_back(y);
        }

        sort(allY.begin() ,allY.end());
        allY.erase(unique(allY.begin() , allY.end()) , allY.end());
        N = allY.size();

        for(int i = 0; i < 2; ++i) for(int j = 0; j < 4 * N; ++j)
            treeUP[i][j] = treeDW[i][j] = ll(5e18);

        ll ans = ll(5e18);
      
        sort(v.begin() , v.end());
        for(auto &[x , y , t] : v){
            int ind = lower_bound(allY.begin() , allY.end() , y) - allY.begin();
           
            ans = min(ans , x - y + qry(ind , N , treeUP[t ^ 1]));
            ans = min(ans , x + y + qry(0 , ind + 1 , treeDW[t ^ 1]));
            // update
            upd(ind , y - x , treeUP[t]);
            upd(ind , -y - x , treeDW[t]);
        }
        cout << ans << '\n';
    }
}