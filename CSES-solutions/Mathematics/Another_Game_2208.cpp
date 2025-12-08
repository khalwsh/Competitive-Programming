/* problem statement text */
/*
CSES - Another Game

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn heaps of coins and two players who move alternately. On each move, a player selects some of the nonempty heaps and removes one coin from each heap. The player who removes the last coin wins the game.
Your task is to find out who wins if both players play optimally.
Input
The first input line contains an integer ttt: the number of tests. After this, ttt test cases are described:
The first line contains an integer nnn: the number of heaps.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the number of coins in each heap.
Output
For each test case, print "first" if the first player wins the game and "second" if the second player wins the game.
Constraints

1≤t≤2⋅1051 \le t \le 2 \cdot 10^51≤t≤2⋅105
1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
the sum of all nnn is at most 2⋅1052 \cdot 10^52⋅105

Example
Input:
3
3
1 2 3
2
2 2
4
5 5 4 5

Output:
first
second
first
*/
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
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;}
const int N=2e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=6e18;
//__builtin_clzll(x): the number of zeros at the beginning of the number
//__builtin_ctzll(x): the number of zeros at the end of the number
//__builtin_popcountll(x): the number of ones in the number
//__builtin_parityll(x): the parity (even or odd) of the number of ones
/*=======================================================================================================*/
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
/*=======================================================================================================*/
 
signed main() {
    khaled
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (auto &val: v)cin >> val,val%=2;
        cout<<(count(v.begin(),v.end(),1)>0?"first":"second")<<line;
    }
}