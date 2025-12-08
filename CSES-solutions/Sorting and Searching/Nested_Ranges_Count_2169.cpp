/* problem statement text */
/*
CSES - Nested Ranges Count

Time limit: 1.00 s
Memory limit: 512 MB

Given nnn ranges, your task is to count for each range how many other ranges it contains and how many other ranges contain it.
Range [a,b][a,b][a,b] contains range [c,d][c,d][c,d] if a≤ca \le ca≤c and d≤bd \le bd≤b.
Input
The first input line has an integer nnn: the number of ranges.
After this, there are nnn lines that describe the ranges. Each line has two integers xxx and yyy: the range is [x,y][x,y][x,y].
You may assume that no range appears more than once in the input.
Output
First print a line that describes for each range (in the input order) how many other ranges it contains.
Then print a line that describes for each range (in the input order) how many other ranges contain it.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤x<y≤1091 \le x < y \le 10^91≤x<y≤109

Example
Input:
4
1 6
2 4
4 8
3 6

Output:
2 0 0 0
0 1 0 1
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
int n;
array<int,3>segments[N];
vector<int>contain(){
    ordered_multiset<int>os;
    for(int i = 0;i<n;i++)os.insert(segments[i][1]);
    sort(segments , segments + n , [](array<int , 3>&a , array<int , 3>&b)->bool {
        if(a[0] != b[0])return a[0] < b[0];
        return a[1] > b[1];
    });
    vector<int>res(n);
    for(int i = 0;i<n;++i) {
        os.erase(os.find_by_order(os.order_of_key(segments[i][1])));
        res[segments[i][2]] = (int)os.order_of_key(segments[i][1] + 1);
    }
    return res;
}
vector<int>contained(){
    ordered_multiset<int>x;
    for(int i = 0;i<n;i++)x.insert(segments[i][1]);
    sort(segments , segments + n, [](auto a, auto b) {
            auto [a1, a2, a3] = a;
            auto [b1, b2, b3] = b;
            if (a1 != b1) return a1 > b1;
            return a2 < b2;
    });
 
    vector<int> ans2(n);
    for (int j = 0 ;j < n;j ++) {
        int b = segments[j][1];
        int i = segments[j][2];
        x.erase(x.find_by_order(x.order_of_key(b)));
        ans2[i] = (int)x.size() - x.order_of_key(b);
    }
    return ans2;
}
signed main() {
    khaled
    cin>>n;
    for(int i = 0;i<n;i++) {
        cin>>segments[i][0]>>segments[i][1];
        segments[i][2] = i;
    }
    for(auto &val:contain()) {
        cout<<val<<" ";
    }
    cout<<line;
    for(auto &val:contained()) {
        cout<<val<<" ";
    }
}
 