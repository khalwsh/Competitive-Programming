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
const int N = 4e5 + 5;
const int mod = 1e9 + 7;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
template<class T>
struct Fenwick{
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
        N = log2_floor(n) + 1;
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    T get(int pos) {
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
    int lower_bound(T t){
        T sum = 0;
        int pos = 0;
        for(int i = N; i >= 0; i--){
            int next_pos = pos + (1 << i);
            if(next_pos <= n && sum + tree[next_pos - 1] < t){
                sum += tree[next_pos - 1];
                pos = next_pos;
            }
        }
        return pos; // zero-based index
    }
};
vector<pair<int , int>>Horizontal[2 * N] , Vertical[2 * N];
signed main() {
    khaled
    int t;
    cin>>t;
    Fenwick<ll> seg;
    seg.init(2 * N);
    while(t--) {
        int n;cin>>n;
        vector<array<int , 4>>inital(n);
        vector<int>all;
        for(int i = 0;i < n;i++) {
            cin>>inital[i][0]>>inital[i][1]>>inital[i][2]>>inital[i][3];
            all.emplace_back(inital[i][0]);
            all.emplace_back(inital[i][1]);
            all.emplace_back(inital[i][2]);
            all.emplace_back(inital[i][3]);
        }
        sort(all.begin() , all.end());
        all.erase(unique(all.begin() , all.end()) , all.end());
        for(int i = 0;i < n;i++) {
            inital[i][0] = lower_bound(all.begin() , all.end() , inital[i][0]) - all.begin();
            inital[i][1] = lower_bound(all.begin() , all.end() , inital[i][1]) - all.begin();
            inital[i][2] = lower_bound(all.begin() , all.end() , inital[i][2]) - all.begin();
            inital[i][3] = lower_bound(all.begin() , all.end() , inital[i][3]) - all.begin();
        }
        int mx = -1;
        for(int i = 0;i < n;i++) {
            int x1 , x2 , y1 , y2;
            x1 = inital[i][0];y1 = inital[i][1];
            x2 = inital[i][2];y2 = inital[i][3];
            if(x1 > x2)swap(x1 , x2);
            if(y1 > y2)swap(y1 , y2);
            mx = max({mx ,x1 , x2 , y1 , y2});
            if(x1 == x2) {
                // vertical
                Vertical[x1].emplace_back(y1 , y2);
            }else {
                // horziontal
                Horizontal[x1].emplace_back(y1 , 1);
                Horizontal[x2].emplace_back(y2 , -1);
            }
        }
        ll res = 0;
        for(int i = 0;i <= all.size();i++) {
            for(auto &val:Horizontal[i]) {
                if(val.second == 1)
                    seg.add(val.first , val.second);
            }
            for(auto &val:Vertical[i]) {
                res += seg.query(val.first , val.second);
            }
            for(auto &val:Horizontal[i]) {
                if(val.second == -1)
                    seg.add(val.first , val.second);
            }
            Horizontal[i].clear();
            Vertical[i].clear();
        }
        for(int i = 0;i <= all.size();i++) {
            seg.add(i , -seg.query(i , i));
        }
        cout<<res<<line;
    }
}