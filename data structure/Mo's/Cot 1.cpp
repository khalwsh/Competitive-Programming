#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
//#define int long long
#define double long double
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
int SafeMul(int a,int b,int m){if(b==0)return 0;int res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 1e5+5;
const int mod=1e9+7;
//const int MOD = 998244353;
const long long inf=3e18+100;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-10;
/*==============================================  KHALWSH  ==============================================*/
int n,m;
vector<int>adj[N];
const int k = 19;
const int SQ = 450;
int St[N],En[N],Tree[2 * N],Timer = 0,parent[N],UP[k][N],depth[N],res[N],Weights[N],Freq[N],Bucket[SQ];
int comp[N],CompSize = 0;
bool odd[N];
void dfs(int node = 0,int par = 0){
    parent[node] = par;
    depth[node] = (node == 0?0:(depth[par] + 1));
    St[node] = Timer;
    Tree[Timer++] = node;
    for(auto &val:adj[node]){
        if(val == par)continue;
        dfs(val,node);
    }
    Tree[Timer] = node;
    En[node] = Timer++;
}
void build(){
    for(int i=0;i<n;i++){
        UP[0][i] = parent[i];
    }
    for(int i=1;i<k;i++){
        for(int j=0;j<n;j++){
            UP[i][j] = UP[i-1][UP[i-1][j]];
        }
    }
}
int Walk(int node,int kth){
    for(int i=0;i<k;i++){
        if(kth & (1<<i)){
            node = UP[i][node];
        }
    }
    return node;
}
int LCA(int a,int b){
    if(depth[a] < depth[b])swap(a,b);
    a = Walk(a,depth[a] - depth[b]);
    if(a == b)return a;
    for(int i=k - 1;i>=0;i--){
        if(UP[i][a] != UP[i][b]){
            a = UP[i][a];
            b = UP[i][b];
        }
    }
    assert(UP[0][a] == UP[0][b]);
    return UP[0][a];
}
void compress() {
    sort(comp, comp + CompSize);
    CompSize = (int)(unique(comp, comp + CompSize) - comp);
    for (int i = 0; i < n; i++) {
        Weights[i] = (int)(lower_bound(comp, comp + CompSize, Weights[i]) - comp);
    }
}
int BLOCK_SIZE = 317;
struct Query{
    int l , r,id,kth,lca;
    Query(int L,int R,int Kth,int I,int LL){
        l = L;
        r = R;
        id = I;
        kth = Kth;
        lca = LL;
    }
    bool operator < (const Query &other) const{
        int n1 = l / BLOCK_SIZE, n2 = other.l / BLOCK_SIZE;
        if(n1 != n2) return n1 < n2;
        return (n1 % 2) ? r > other.r : r < other.r;
    }
};
void add(int MoIdx){
    Freq[Weights[Tree[MoIdx]]]++;
    Bucket[Weights[Tree[MoIdx]]/SQ]++;
}
void remove(int MoIdx){
    Freq[Weights[Tree[MoIdx]]]--;
    Bucket[Weights[Tree[MoIdx]]/SQ]--;
}
void upd(int ind){
    odd[Tree[ind]]^=true;
    if(odd[Tree[ind]])add(ind);
    else remove(ind);
}
void Mo(vector<Query> &queries){
    int MoLeft = 0,MoRight = -1;
    for(auto &q: queries){
        while(MoRight < q.r) upd(++MoRight);
        while(MoLeft > q.l) upd(--MoLeft);
        while(MoRight > q.r) upd(MoRight--);
        while(MoLeft < q.l) upd(MoLeft++);
        add(St[q.lca]);
        int ans = 0;
        for(int l=0,i=0;l<N;l+=SQ,i++){
            if(Bucket[i] < q.kth){
                q.kth -= Bucket[i];
            }else{
                for(int j=l;j<l + SQ;j++){
                    q.kth -= Freq[j];
                    if(q.kth <= 0) {
                        ans = j;
                        break;
                    }
                }
                break;
            }
        }
        remove(St[q.lca]);
        res[q.id] = ans;
    }
}
signed main() {
    khaled
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>Weights[i],comp[i] = Weights[i];
    CompSize = n;
    compress();
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    dfs();
    build();
    BLOCK_SIZE = (int)sqrt(2 * n) + 10;
    vector<Query>queries;
    for(int i=0;i<m;i++){
        int u,v,kth;
        cin>>u>>v>>kth;
        u--,v--;
        if(St[u] > St[v])swap(u,v);
        int L = LCA(u,v);
        if(L == u){
            queries.emplace_back(St[u] + 1,St[v],kth,i,L);
        }else{
            queries.emplace_back(En[u],St[v],kth,i,L);
        }
    }
    sort(queries.begin(),queries.end());
    Mo(queries);
    for(int i=0;i<m;i++){
        cout<<comp[res[i]]<<line;
    }
}
