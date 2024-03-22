//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-9;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
const int N=5e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=9e18+1;
//__builtin_clzll(x): the number of zeros at the beginning of the number
//__builtin_ctzll(x): the number of zeros at the end of the number
//__builtin_popcountll(x): the number of ones in the number
//__builtin_parityll(x): the parity (even or odd) of the number of ones
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
extern struct node* Empty;

struct node{
    int sum;
    node*lf,*rt;
    node(){
        sum=0;
        lf =rt = this;
    }
    node(int value,node* lf = Empty, node* rt = Empty):lf(lf) , rt(rt) , sum(value){}
};

node*Empty = new node();

node* roots[N];

node* insert(int val,node*cur,int ns=-1e9,int ne=1e9){
    if(val < ns or val > ne)return cur;
    if(ne == ns){
        return new node(cur->sum+1);
    }
    int mid=ns+(ne-ns)/2;
    node*LF = insert(val, cur->lf,ns,mid);
    node*RT = insert(val,cur->rt,mid+1,ne);
    return new node(LF->sum+RT->sum,LF,RT);
}

int query(int k , node *en, node*stm1, int ns=-1e9, int ne=1e9){
    if(ns==ne)return ns;
    int LeftSz=en->lf->sum-stm1->lf->sum;
    int mid=ns+(ne-ns)/2;
    if(k<=LeftSz)return query(k,en->lf,stm1->lf,ns,mid);
    return query(k-LeftSz,en->rt,stm1->rt,mid+1,ne);
}
signed main() {
    khaled
    roots[0]=Empty;
    int m,xx;
    int n;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>xx;
        roots[i]= insert(xx,roots[i-1]);
    }
    while(m--){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<query(k,roots[r],roots[l-1])<<line;
    }
}
