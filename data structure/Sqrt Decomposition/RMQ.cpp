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
const int N = 3e5+5;
const int mod=5000000;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
const int sq = 400;
int n,v[N],q,pre[sq];
int solve(int l,int r){
    int st = l/sq;
    int en = r/sq;
    int res = inf;
    for(int i = l;i<min(r,(st+1)*sq);i++)res = min(res,v[i]);
    for(int i = max(l,(en)*sq);i<=r;i++)res = min(res,v[i]);
    for(int i= st + 1;i<en;i++){
        res = min(res,pre[i]);
    }
    return res;
}
signed main() {
    khaled
    cin>>n;
    for(int i=0;i<sq;i++)pre[i] = inf;
    for(int i=0;i<n;i++)cin>>v[i];
    for(int i=0;i<n;i++){
        pre[i/sq] = min(pre[i/sq],v[i]);
    }
    cin>>q;
    while(q--){
        int l,r;cin>>l>>r;
        cout<<solve(l,r)<<line;
    }
}