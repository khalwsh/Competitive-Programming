#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
const int N = 1e6+9;
int n , m , id;
struct Node{
    int l , r , s;
}tree[20*N];
int newLeaf(int v){
    tree[id] = Node{-1,-1,v};
    return id++;
}
int newPar(int l , int r){
    tree[id] = Node{l,r,0};
    tree[id].s += tree[l].s;
    tree[id].s += tree[r].s;
    return id++;
}
int build(int l = 0 , int r = m){
    if(r - l == 1) return newLeaf(0);
    int mid = (l+r)/2;
    return newPar( build(l,mid) , build(mid,r) );
}
int copy(int i , int v , int x , int l = 0 , int r = m){
    if(r - l == 1) return newLeaf(tree[x].s + v);
    int mid = (l+r)/2;
    if(i < mid) return newPar( copy(i,v , tree[x].l , l , mid) , tree[x].r);
    return newPar( tree[x].l , copy(i,v, tree[x].r , mid , r) );
}
int qry(int lx , int rx , int prv , int cur , int l = 0 , int r = m){
    if(l >= lx && r <= rx) return tree[cur].s - tree[prv].s;
    if(r <= lx || l >= rx) return 0;
    int mid = (l+r)/2;
    return qry(lx,rx, tree[prv].l , tree[cur].l ,l,mid) + qry(lx,rx, tree[prv].r , tree[cur].r,mid,r);
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    cin >> n;
    int a[n+1];
    for(int i = 1; i <= n; ++i) cin >> a[i];
    m = 1e6 + 9;

    int snapshot[n+1];
    snapshot[0] = build();
    for(int i = 1; i <= n; ++i){
        snapshot[i] = copy(a[i] , +1 , snapshot[i-1]);
        cerr << tree[snapshot[i]].s << '\n';;
    }

    int q; cin >> q;
    while(q--){
        int i , j , k; cin >> i >> j >> k;
        cout << qry(k , m , snapshot[i-1] , snapshot[j]) << '\n';
    }

    id = 0; // reset
}