/* problem statement text */
/*
CSES - Finding Periods

Time limit: 1.00 s
Memory limit: 512 MB

A period of a string is a prefix that can be used to generate the whole string by repeating the prefix. The last repetition may be partial. For example, the periods of abcabca are abc, abcabc and abcabca.
Your task is to find all period lengths of a string.
Input
The only input line has a string of length nnn consisting of characters a–z.
Output
Print all period lengths in increasing order.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
abcabca

Output:
3 6 7
*/
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
//#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
//#define int long long
//#define double long double
#define line '\n'
typedef long long ll;
typedef double ld;
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
const int N = 1e6+5;
const int mod=1e9+7;
//const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
vector<int64_t> pref, suf;
const uint64_t HashMod = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (HashMod / 3) + (HashMod / 3);
uint64_t base_pow[N];
 
int64_t MUL(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}
 
void init() {
    base_pow[0] = 1;
    for (int i = 1; i < N; i++) {
        base_pow[i] = MUL(base_pow[i - 1], base);
    }
}
struct PolyHash {
    /// Remove suf vector and usage if reverse hash is not required for more speed
        template<typename T>
    PolyHash(const vector<T> &ar) {
        if (!base_pow[0]) init();
 
        int n = ar.size();
        assert(n < N);
        pref.resize(n + 3, 0), suf.resize(n + 3, 0);
 
        for (int i = 1; i <= n; i++) {
            pref[i] = MUL(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= HashMod) pref[i] -= HashMod;
        }
 
        for (int i = n; i >= 1; i--) {
            suf[i] = MUL(suf[i + 1], base) + ar[i - 1] + 997;
            if (suf[i] >= HashMod) suf[i] -= HashMod;
        }
    }
 
    explicit PolyHash(string str) : PolyHash(vector<char>(str.begin(), str.end())) {}
 
    uint64_t get_hash(int l, int r) {
        int64_t h = pref[r + 1] - MUL(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + HashMod : h;
    }
 
    uint64_t rev_hash(int l, int r) {
        int64_t h = suf[l + 1] - MUL(base_pow[r - l + 1], suf[r + 2]);
        return h < 0 ? h + HashMod : h;
    }
};
 
signed main() {
    khaled
    string s;cin>>s;
    PolyHash p(s);
    for(int i = 1;i<=s.size();i++){
        ll pre = p.get_hash(0 , i - 1);
        bool fail = false;
        for(int j=i;j<=s.size();j+=i){
            if(j + i - 1 >= s.size()){
                int len = (int)s.size() - j;
                if(p.get_hash(0 , len - 1) == p.get_hash(j , s.size() - 1)){
                    break;
                }
                fail = true;
                break;
            }
            if(p.get_hash(j , j + i - 1) == pre){
                continue;
            }else{
                fail = true;
                break;
            }
        }
        if(!fail)
            cout<<i<<" ";
    }
}