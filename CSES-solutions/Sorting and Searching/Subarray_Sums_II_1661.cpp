/* problem statement text */
/*
CSES - Subarray Sums II

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to count the number of subarrays having sum xxx.
Input
The first input line has two integers nnn and xxx: the size of the array and the target sum xxx.
The next line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the contents of the array.
Output
Print one integer: the required number of subarrays.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤x,ai≤109-10^9 \le x,a_i \le 10^9−109≤x,ai​≤109

Example
Input:
5 7
2 -1 3 5 -2

Output:
2
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
const int N=2e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17+1;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846,eps=1e-9;
/*==============================================  KHALWSH  ==============================================*/
int query(int l,int r,vector<int>&s){
    return s[r]-(l==0?0:s[l-1]);
}
signed main() {
    khaled
    int n,x;
    cin>>n>>x;
    int res=0;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    vector<int>arr(v);
    for(int i=1;i<n;i++)v[i]+=v[i-1];
    map<int,int>mp;
    for(int i=n-1;i>=0;i--){
        int need=x;
        if(x==arr[i])res++;
        if(i!=0){
            need+=v[i-1];
        }
        res+=mp[need];
        mp[v[i]]++;
    }
    cout<<res<<line;
}