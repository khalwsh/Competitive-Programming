/* problem statement text */
/*
CSES - Towers

Time limit: 1.00 s
Memory limit: 512 MB

You are given nnn cubes in a certain order, and your task is to build towers using them. Whenever two cubes are one on top of the other, the upper cube must be smaller than the lower cube.
You must process the cubes in the given order. You can always either place the cube on top of an existing tower, or begin a new tower. What is the minimum possible number of towers?
Input
The first input line contains an integer nnn: the number of cubes.
The next line contains nnn integers k1,k2,…,knk_1,k_2,\ldots,k_nk1​,k2​,…,kn​: the sizes of the cubes.
Output
Print one integer: the minimum number of towers.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ki≤1091 \le k_i \le 10^91≤ki​≤109

Example
Input:
5
3 8 2 1 5

Output:
2
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
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
const int N=1e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17+1;
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
// open file ------ notepad filename.cpp
// compile ------ g++ filename.cpp -o filename
// run ------ cp.exe
 
signed main() {
    khaled
    int n;
	cin>>n;
	multiset<int>s;
	int x;
    for(int i=0;i<n;++i)
    {
    	cin>>x;
    	auto it=s.upper_bound(x);
    	if(it==s.end())s.insert(x);
    	else
    	{
    		s.erase(it);
    		s.insert(x);
	    }
    }
    cout<<s.size()<<endl;
}