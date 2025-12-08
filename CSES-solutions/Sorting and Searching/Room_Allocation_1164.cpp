/* problem statement text */
/*
CSES - Room Allocation

Time limit: 1.00 s
Memory limit: 512 MB

There is a large hotel, and nnn customers will arrive soon. Each customer wants to have a single room.
You know each customer's arrival and departure day. Two customers can stay in the same room if the departure day of the first customer is earlier than the arrival day of the second customer.
What is the minimum number of rooms that are needed to accommodate all customers? And how can the rooms be allocated?
Input
The first input line contains an integer nnn: the number of customers.
Then there are nnn lines, each of which describes one customer. Each line has two integers aaa and bbb: the arrival and departure day.
Output
Print first an integer kkk: the minimum number of rooms required.
After that, print a line that contains the room number of each customer in the same order as in the input. The rooms are numbered 1,2,…,k1,2,\ldots,k1,2,…,k. You can print any valid solution.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a≤b≤1091 \le a \le b \le 10^91≤a≤b≤109

Example
Input:
3
1 2
2 4
4 4

Output:
2
1 2 1
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
const int N = 2e5+5;
//const int mod=1e9+7;
//const int MOD = 998244353;
const long long inf=3e18+100;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-10;
/*==============================================  KHALWSH  ==============================================*/
int n;
pair<int,int>arr[N];
int comp[2 * N];
int partial[N * 3];
vector<pair<int,int>>queries[N * 2];
vector<int>UnBook[N * 2];
int ans[N];
signed main() {
    khaled
    cin >> n;
    int j = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        arr[i] = make_pair(x, y);
        comp[j] = x;
        comp[j + 1] = y;
        j += 2;
    }
    sort(comp, comp + j);
    int s = unique(comp, comp + j) - comp;
    for (int i = 0; i < n; i++) {
        arr[i].first = lower_bound(comp, comp + s, arr[i].first) - comp;
        arr[i].second = lower_bound(comp, comp + s, arr[i].second) - comp;
    }
    for (int i = 0; i < n; i++) {
        partial[arr[i].first]++;
        partial[arr[i].second + 1]--;
    }
    for (int i = 1; i < 3 * N; i++) {
        partial[i] += partial[i - 1];
        assert(partial[i] >= 0);
    }
    int res = *max_element(partial, partial + 3 * N);
    set<int> free;
    for (int i = 0; i < res; i++) {
        free.insert(i);
    }
    cout << res << line;
    for (int i = 0; i < n; i++) {
        queries[arr[i].first].emplace_back(arr[i].second, i);
    }
    for (int i = 0; i < 2 * N; i++) {
        for (auto &val: UnBook[i])free.insert(val);
        for (auto &val: queries[i]) {
            int temp = *free.begin();
            ans[val.second] = temp;
            free.erase(temp);
            UnBook[val.first + 1].emplace_back(temp);
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] + 1 << " ";
}