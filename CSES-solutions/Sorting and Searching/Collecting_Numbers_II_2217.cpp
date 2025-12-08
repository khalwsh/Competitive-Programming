/* problem statement text */
/*
CSES - Collecting Numbers II

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array that contains each number between 1…n1 \dots n1…n exactly once. Your task is to collect the numbers from 111 to nnn in increasing order.
On each round, you go through the array from left to right and collect as many numbers as possible.
Given mmm operations that swap two numbers in the array, your task is to report the number of rounds after each operation.
Input
The first line has two integers nnn and mmm: the array size and the number of operations.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the numbers in the array.
Finally, there are mmm lines that describe the operations. Each line has two integers aaa and bbb: the numbers at positions aaa and bbb are swapped.
Output
Print mmm integers: the number of rounds after each swap.
Constraints

1≤n,m≤2⋅1051 \le n, m \le 2 \cdot 10^51≤n,m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 3
4 2 1 5 3
2 3
1 5
2 3

Output:
2
3
4
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
// #define int long long
#define line '\n'
typedef long long ll;
typedef long double ld;
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
ll SafeMul(ll a,ll b,ll m){if(b==0)return 0;ll res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 3e5 +5;
const int mod=1e9+7;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
 
signed main() {
    khaled
    int n , q;
    cin>>n>>q;
    vector<int>values(n + 1);
    for(int i = 1;i<=n;i++)cin>>values[i];
    vector<int>positions(n+1);
    for(int i=1;i<=n;i++){
        positions[values[i]]=i;
    }
    int res=1;
    for(int i=2;i<=n;i++){
        if(positions[i]<positions[i-1])res++;
    }
    set<pair<int, int> > updatedPairs;
    int count = res;
    for (int i = 0; i < q; i++) {
        int l , r;cin>>l>>r;
        if (values[l] + 1 <= n)
            updatedPairs.insert(
                { values[l], values[l] + 1 });
        if (values[l] - 1 >= 1)
            updatedPairs.insert(
                { values[l] - 1, values[l] });
        if (values[r] + 1 <= n)
            updatedPairs.insert(
                { values[r], values[r] + 1 });
        if (values[r] - 1 >= 1)
            updatedPairs.insert(
                { values[r] - 1, values[r] });
        for (auto swapped : updatedPairs)
            count -= positions[swapped.first]
                     > positions[swapped.second];
 
        swap(values[l], values[r]);
 
        positions[values[l]] = l;
        positions[values[r]] = r;
 
        for (auto swapped : updatedPairs)
            count += positions[swapped.first] > positions[swapped.second];
        updatedPairs.clear();
        cout<<count<<line;
    }
}
 
 