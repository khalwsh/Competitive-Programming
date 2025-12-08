/* problem statement text */
/*
CSES - Sum of Four Values

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers, and your task is to find four values (at distinct positions) whose sum is xxx.
Input
The first input line has two integers nnn and xxx: the array size and the target sum.
The second line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the array values.
Output
Print four integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
1≤x,ai≤1091 \le x,a_i \le 10^91≤x,ai​≤109

Example
Input:
8 15
3 2 5 8 1 3 2 3

Output:
2 4 6 7
*/
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
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
int SafeMul(int a,int b,int m){if(b==0)return 0;int res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 2e5+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n,x;
int v[1001];
signed main() {
    khaled
    cin>>n>>x;
    for(int i=0;i<n;i++)cin>>v[i];
    map<int,pair<int,int>>mp;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int missing = x - v[i] - v[j];
            if(mp.count(missing)){
                cout<<mp[missing].first+1<<" "<<1+mp[missing].second<<" "<<i+1<<" "<<j+1;
                exit(0);
            }
        }
        for(int j=0;j<i;j++){
            mp[v[j]+v[i]] = make_pair(j,i);
        }
    }
    cout<<"IMPOSSIBLE"<<line;
}