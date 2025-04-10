#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
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
const int N = 8e5+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n,m;
const int k = 20,SQ = 400;
vector<int>adj[N];
int Cost[N],UP[k][N],Parent[N],LinearTree[N],Timer = 0,Depth[N],root = 0,ST[N],EN[N],CompressionValue = 1,ans[N],res = 0,Freq[N];
bool IsOdd[N];
void MarkDepth(int node,int par,int c = 0) {
    Depth[node] = c;
    for (auto &val: adj[node]) {
        if (val == par)continue;
        MarkDepth(val, node, c + 1);
    }
}
void Rooting() {
    queue<pair<int, int>> q;
    q.emplace(root, -1);
    while (!q.empty()) {
        int node = q.front().first;
        int par = q.front().second;
        q.pop();
        for (auto &val: adj[node]) {
            if (val != par) {
                Parent[val] = node;
                q.emplace(val, node);
            }
        }
    }
    Parent[root] = root;
}
void BuildLiftingTable() {
    MarkDepth(root, -1);
    for (int i = 0; i < n; i++) {
        UP[0][i] = Parent[i];
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            UP[i][j] = UP[i - 1][UP[i - 1][j]];
        }
    }
}
int Walk(int node,int kth) {
    if (Depth[node] < kth)return -1;
    for (int i = 0; i < k; i++) {
        if (kth & (1 << i)) {
            node = UP[i][node];
        }
    }
    return node;
}
int LCA(int a,int b) {
    if (Depth[b] > Depth[a])swap(a, b);
    a = Walk(a, Depth[a] - Depth[b]);
    if (a == b)return a;
    for (int i = k - 1; i >= 0; i--) {
        if (UP[i][a] != UP[i][b]) {
            a = UP[i][a];
            b = UP[i][b];
        }
    }
    return Parent[a];
}
void Linear(int node,int par) {
    LinearTree[Timer] = node;
    ST[node] = Timer;
    Timer++;
    for (auto &val: adj[node]) {
        if (val == par)continue;
        Linear(val, node);
    }
    LinearTree[Timer] = node;
    EN[node] = Timer;
    Timer++;
}
map<int,int>compression;
struct Query {
    int l, r, lca , idx ;
    bool work;

    Query(int L = 0, int R = 0, int Lca = 0,int i = 0, bool W = false) {
        l = L;
        r = R;
        lca = Lca;
        idx = i;
        work = W;
    }

    bool operator<(const Query &other) {
        return make_pair(l / SQ, r) < make_pair(other.l / SQ, other.r);
    }
};
void AddElement(int node){
    Freq[Cost[node]]++;
    if(Freq[Cost[node]]==1)res++;
}

void EraseElement(int node){
    Freq[Cost[node]]--;
    if(Freq[Cost[node]]==0)res--;
}

void UpdateMoState(int node){
    IsOdd[node]^=true;
    return void(IsOdd[node]? AddElement(node): EraseElement(node));
}

signed main() {
    khaled
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> Cost[i];
        if (compression.count(Cost[i])) {
            Cost[i] = compression[Cost[i]];
            continue;
        }
        compression[Cost[i]] = CompressionValue++;
        Cost[i] = compression[Cost[i]];
    }
    for (int j = 0; j < n - 1; j++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    Rooting();
    BuildLiftingTable();
    Linear(root, -1);
    vector<Query> queries;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (ST[l] > ST[r])swap(l, r);
        int lca = LCA(l, r);
        if (lca == l) {
            queries.emplace_back(ST[lca], ST[r], lca,i, false);
        } else {
            queries.emplace_back(EN[l], ST[r], lca, i,true);
        }
    }
    sort(queries.begin(), queries.end());
    int MoRight = -1, MoLeft = 0;
    for (auto &val: queries) {
        int idx = val.idx;
        int l = val.l;
        int r = val.r;
        while (MoRight < r) {
            MoRight++;
            UpdateMoState(LinearTree[MoRight]);
        }
        while (MoLeft > l) {
            MoLeft--;
            UpdateMoState(LinearTree[MoLeft]);
        }
        while (MoRight > r) {
            UpdateMoState(LinearTree[MoRight]);
            MoRight--;
        }
        while (MoLeft < l) {
            UpdateMoState(LinearTree[MoLeft]);
            MoLeft++;
        }
        if (val.work)UpdateMoState(val.lca);
        ans[idx] = res;
        if (val.work) UpdateMoState(val.lca);
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << line;
    }
}

