/* problem statement text */
/*
CSES - Maximum Subarray Sum II

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find the maximum sum of values in a contiguous subarray with length between aaa and bbb.
Input
The first input line has three integers nnn, aaa and bbb: the size of the array and the minimum and maximum subarray length.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Output
Print one integer: the maximum subarray sum.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n
−109≤xi≤109-10^9 \le x_i \le 10^9−109≤xi​≤109

Example
Input:
8 1 2
-1 3 -2 5 3 -5 2 2

Output:
8
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int a2,int a3,int b1,int b2,int b3) {return (a3 - a1) * (b2 - b1) == (a2 - a1) * (b3 - b1);}
const int N=4e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17+1;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846,eps=1e-9;
/*==============================================  KHALWSH  ==============================================*/
int n,a,b;
int v[N],pre[N];
int query(int l,int r){
    return pre[r]-(l==0?0:pre[l-1]);
}
const int k=24;
int sp[k][N];
int dp[N][2];
void build(){
    for(int i=0;i<n;i++)sp[0][i]=pre[i];
    for(int i=1;i<k;i++){
        for(int j=0;j+(1<<i)<=n;j++){
            sp[i][j]=max(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);
        }
    }
}
int Mx(int l,int r){
    if(r-l+1<=0)return 0;
    int lg= log2_floor(r-l+1);
    return max(sp[lg][l],sp[lg][r-(1<<lg)+1]);
}
int solve(int index,int state){
    if(index>n)return -inf;
    if(index==n)return (state==1?0:-inf);
    int &ret=dp[index][state];
    if(~ret)return ret;
    if(state==0){
        int leave=solve(index+1,state);
        if(index+a>n)return leave;
        int take=solve(index+a,1)+ query(index,index+a-1);
        return ret=max(leave,take);
    }else{
        if(a==b)return 0;
        int res=Mx(index,min(n-1,index+b-a-1))-(index==0?0:pre[index-1]);
        return ret=max(0ll,res);
    }
}
signed main() {
    khaled
    cin>>n>>a>>b;
    if(a>n){
        cout<<0<<line;
        exit(0);
    }
    memset(dp,-1,sizeof dp);
    for(int i=0;i<n;i++)cin>>v[i],pre[i]=v[i],pre[i]+=(i==0?0:pre[i-1]);
    build();
    cout<<solve(0,0);
}