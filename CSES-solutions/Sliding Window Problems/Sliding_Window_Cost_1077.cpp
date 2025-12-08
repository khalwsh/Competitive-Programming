/* problem statement text */
/*
CSES - Sliding Window Cost

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate for each window of kkk elements, from left to right, the minimum total cost of making all elements equal.
You can increase or decrease each element with cost xxx where xxx is the difference between the new and the original value. The total cost is the sum of such costs.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Output n−k+1n-k+1n−k+1 values: the costs.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
2 4 3 5 8 1 2 1

Output:
2 2 5 7 7 1
*/
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
// #define int long long
// #define double long double
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
const int N = 3e5+5;
// const int mod=1e9+7;
const int mod = 998244353;
const ll inf=2e9;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left up down
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
std::string convertToBase(ll number, int base) {
	if (base < 2 || base > 36) {
		throw std::invalid_argument("Base must be in the range 2-36.");
	}
 
	if (number == 0) {
		return "0";
	}
 
	std::string result;
	bool isNegative = (number < 0);
	if (isNegative) {
		number = -number;
	}
 
	while (number > 0) {
		int remainder = number % base;
		if (remainder < 10) {
			result += '0' + remainder;
		} else {
			result += 'A' + (remainder - 10);
		}
		number /= base;
	}
 
	if (isNegative) {
		result += '-';
	}
 
    // Reverse the string since the remainders produce the number in reverse order
	std::reverse(result.begin(), result.end());
 
	return result;
}
struct BIT{
	int N;
	vector<ll>tree;
	void init(ll x){
		N=1<<x;
		tree.resize(this->N);
	}
	void add(int pos,ll value){
		for(++pos;pos<=N;pos+=pos&-pos)tree[pos-1]+=value;
	}
ll get(int pos){
	ll sum=0;
	for(++pos;pos>0;pos-=pos&-pos)sum+=tree[pos-1];
		return sum;
}
int find(ll t){
	int st=0;
	for(int sz=N>>1;sz;sz>>=1){
		if(tree[st+sz-1]<t){
			t-=tree[(st+=sz)-1];
		}
	}
	return st;
}
};
struct Multiset{
	BIT bit;
	Multiset(int x){
		bit.init(x);
		bit.add(0,-1);
	}
	int size(){
		return bit.get(bit.N-1)+1;
	}
	void insert(int value){
		bit.add(value,1);
	}
	void erase(int value){
		bit.add(value,-1);
	}
	int count(int x){
		return bit.get(x)-bit.get(x-1);
	}
	int at(int x){
		return bit.find(x);
	}
};
struct Fenwick{
	int n;
	vector<ll>tree;
	void init(int _n){
		n=_n;
		tree.resize(this->n);
	}
	void add(int pos,ll value){
		for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
	}
ll get(int pos) {
	ll sum = 0;
	for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
		return sum;
}
ll query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};
 
ll v[N] , comp[N];
signed main() {
	khaled
	int n,k;
	cin>>n>>k;
	for(int i = 0;i<n;i++){
		cin>>v[i];
		comp[i] = v[i];
	}
	sort(comp , comp + n);
	int s = unique(comp , comp + n) - comp;
	for(int i = 0;i<n;i++){
		v[i] = lower_bound(comp , comp + s , v[i]) - comp;
	}
 
	Multiset ms(19);
	Fenwick f , c;
	f.init(s + 10) , c.init(s + 10);
	for(int i=0;i<k;i++)ms.insert(v[i]) , f.add(v[i] , comp[v[i]]) , c.add(v[i] , 1);
	vector<ll>res;
	for(int i=0;i<n;i++){
		if(res.size()==n-k+1)break;
		int sz=ms.size();
		if(sz&1){
			ll meadian = ms.at((k+1)/2-1);
			// if(i == n - k){
			// 	for(int i = 0;i<sz;i++)
			// 		cout<<ms.at(i)<<" ";
			// 	cout<<line;
			// }
			res.emplace_back(c.query(0 , meadian) * comp[meadian] - f.query(0 , meadian) + (f.query(meadian , s + 9) - c.query(meadian , s + 9) * comp[meadian]));
		}else{
			ll meadian = max(ms.at((k)/2),ms.at((k)/2-1));
			// cout<<meadian<<line;
			// if(i == n - k)cout<<line<<meadian<<line;
			res.emplace_back(c.query(0 , meadian) * comp[meadian] - f.query(0 , meadian) + (f.query(meadian , s + 9) - c.query(meadian , s + 9) * comp[meadian]));
		}
		f.add(v[i], -comp[v[i]]);
		c.add(v[i] , -1);
		f.add(v[i + k] , comp[v[i + k]]);
		c.add(v[i + k] , 1);
		ms.erase(v[i]);
		ms.insert(v[i+k]);
	}
	for(auto &val:res)cout<<val<<" ";
}