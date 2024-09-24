#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
#define int long long
//#define double long double
#define line '\n'
typedef long long ll;
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
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
const int mod=1e9+7;
//const int mod = 998244353;
const int inf=1e9;
const double pi=3.14159265350979323846,eps=1e-10;
/*==============================================  KHALWSH  ==============================================*/
int even[26][N];
int odd[26][N];
int n;
ll query(int c , int l , int r , int pref[26][N]) {
    if(l < 0 || r >= n)return 0;
    return pref[c][r] - (l ? pref[c][l - 1]: 0);
}
signed main() {
    khaled
    int t;
    cin >> t;
    while (t--) {
        int n;cin>>n;
        int k;cin>>k;
        int g = 0;
        // bool z= false;
        map<int , int>mp;
        for(int i = 0;i < n;i++) {
            int x;cin>>x;
            mp[x]++;
            g = __gcd(g , x);
        }
        vector<int>can;
        if(n > 1) can.emplace_back(0);
        for(ll i = g;i <= 3e9 && (can.size() != n);i += g) {
            can.emplace_back(i);
        }
        ll Mex = 0;
        can.erase(unique(can.begin() , can.end()) , can.end());
        for(auto &val:can) {
            if(val != Mex) {
                if(Mex + k <= val) {
                    Mex += k - 1;
                    k = 1;
                    break;
                }
                k -= val - Mex;
                Mex = val + 1;
            }else
                Mex++;
        }
        cout<<Mex + k - 1<<line;
    }
}struct Manacher {
	vector<int>p;
	string T;
	void build(string &s) {
		string t;
		T = s;
		for(auto &val:s)t += '#' , t += val;
		t += '#';
		int n = (int)t.size();
		p.resize(n , 1);
		int l = 1 , r = 1;
		for(int i = 1;i < n;i++) {
			p[i] = max(0 , min(r - i , p[l + r - i]));
			while(i - p[i] >= 0 and i + p[i] < n and t[i + p[i]] == t[i - p[i]])p[i]++;
			if(p[i] + i > r) {
				r = i + p[i];
				l = i - p[i];
			}
		}
	}
	int GetLongest(int center , bool odd = true) {
		int NewCenter = 2 * center + !odd + 1;
		return p[NewCenter] - 1;
	}
	bool IsPalndrome(int l , int r) {
		return (r - l + 1) <= GetLongest((l + r) / 2 , l % 2 == r % 2);
	}
	string LongestPalndromeSubStr() {
		int m = 0 , st = -1;
		for(int i = 0;i < T.size();i++) {
			if(GetLongest(i , false) >= m) {
				m = GetLongest(i , false);
				st = i;
			}
			if(GetLongest(i , true) >= m) {
				m = GetLongest(i , true);
				st = i;
			}
		}
		if(m & 1) {
			return T.substr(st - m / 2 , m);
		}
		return T.substr(st - m / 2 + 1 , m);
	}
};