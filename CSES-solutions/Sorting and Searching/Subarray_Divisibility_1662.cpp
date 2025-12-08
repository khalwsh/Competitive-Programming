/* problem statement text */
/*
CSES - Subarray Divisibility

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to count the number of subarrays where the sum of values is divisible by nnn.
Input
The first input line has an integer nnn: the size of the array.
The next line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the contents of the array.
Output
Print one integer: the required number of subarrays.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤ai≤109-10^9 \le a_i \le 10^9−109≤ai​≤109

Example
Input:
5
3 1 2 7 4

Output:
1
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
const int N = 1e6+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n;
int arr[N];
int CountSubArrayDivision(int k){
    map<int,int>mp;
    int sum = 0;
    mp[sum] = 1;
    for(int i=0;i<n;i++){
        sum+=arr[i];
        mp[add(sum,0,k)]++;
    }
    int res = 0;
    for(auto &val:mp){
        res += val.second * (val.second - 1) / 2;
    }
    return res;
}
signed main() {
    khaled
    cin>>n;
    for(int i=0;i<n;i++)cin>>arr[i];
    cout<<CountSubArrayDivision(n);
}
 
 