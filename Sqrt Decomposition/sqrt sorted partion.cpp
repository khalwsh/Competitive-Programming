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
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n,q;
const int sq = 317;
vector<int>pre[sq];
int v[N];
void Modify(int i,int value){
    int block = i/sq;
    int temp = i;
    i = lower_bound(pre[block].begin(),pre[block].end(),v[i]) - pre[block].begin();
    v[temp] = value;
    pre[block][i] = value;
    while(i+1<pre[block].size() && pre[block][i]>pre[block][i+1])swap(pre[block][i],pre[block][i+1]),i++;
    while(i-1>=0 && pre[block][i]<pre[block][i-1])swap(pre[block][i],pre[block][i-1]),i--;
}
int query(int l,int r,int x){
    int res = 0;
    int st = l/sq, en = r/sq;
    for(int i = l;i<min(r+1,(st+1)*sq);i++){
        res += (x >= v[i]);
    }
    if(en==st)return res;
    for(int i = en * sq;i<=r;i++){
        res += (x >= v[i]);
    }
    if(en == st+1)return res;
    for(int i = (st+1) ; i < en ;i++){
        if((int)pre[i].size())
            res += (upper_bound(pre[i].begin(),pre[i].end(),x) - pre[i].begin());
    }
    return res;
}
signed main() {
    khaled
    cin>>n>>q;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        v[i] = x;
        pre[i/sq].emplace_back(x);
    }
    for(int i=0;i<sq;i++)sort(pre[i].begin(),pre[i].end());
    while(q--){
        char type;cin>>type;
        if(type=='M'){
            //modify
            int ind , value;
            cin>>ind>>value;ind--;
            Modify(ind,value);
        }else{
            int l,r;cin>>l>>r;
            l--,r--;
            int x;cin>>x;
            cout<<query(l,r,x)<<line;
        }
    }
}