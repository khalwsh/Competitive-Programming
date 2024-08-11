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
const int N = 2e5 + 5;
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
vector<int> suf, group, NewGroup, tempSuf;
int curLen = 0;
void countingSort(int maxGroup) {
    vector<int> count(maxGroup + 1, 0);
    tempSuf.resize(n);

    for (int i = 0; i < n; i++) {
        count[group[min(n - 1, suf[i] + curLen)]]++;
    }
    for (int i = 1; i <= maxGroup; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        tempSuf[--count[group[min(n - 1, suf[i] + curLen)]]] = suf[i];
    }
    for (int i = 0; i < n; i++) {
        suf[i] = tempSuf[i];
    }
}
void radixSort() {
    int maxGroup = max(n, 256);  // Initial max group value for radix sort

    // Sort by the second key (group[i + curLen])
    countingSort(maxGroup);

    // Sort by the first key (group[i])
    curLen = 0;
    countingSort(maxGroup);
}
void build(string &s) {
    suf.clear();
    group.clear();
    NewGroup.clear();
    n = (int)s.size();
    NewGroup.resize(n + 1);
    n++;
    for (int i = 0; i < n; i++) {
        suf.emplace_back(i);
        group.emplace_back(s[i]);
    }
    for (int len = 1;; len *= 2) {
        curLen = len;
        radixSort();
        for (int i = 1; i < n; i++) {
            NewGroup[i] = NewGroup[i - 1] + (group[suf[i - 1]] != group[suf[i]] || group[suf[i - 1] + len] != group[suf[i] + len]);
        }
        for (int i = 0; i < n; i++) {
            group[suf[i]] = NewGroup[i];
        }
        if (NewGroup[n - 1] == n - 1) break;
    }
}
vector<int>lcp;
void BuildLcp(string &s) {
    lcp.resize(n);
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = group[i] - 1; // Corrected index for accessing the previous suffix
        int j = suf[pi];
        while (s[j + k] == s[i + k]) k++;
        lcp[pi] = k; // Store the LCP value at the correct index
        if (k > 0) k--;
    }
}
void init(string &s) {
    suf.clear() , group.clear() , NewGroup.clear() , tempSuf.clear();
    lcp.clear();
    build(s);
    BuildLcp(s);
}
signed main() {
    khaled
    string s;cin>>s;
    init(s);
    ll res = s.size() - suf[1];
    for(int i = 2;i < suf.size();i++) {
        res += (int)s.size() - suf[i] - lcp[i - 1];
    }
    cout<<res<<line;
}
