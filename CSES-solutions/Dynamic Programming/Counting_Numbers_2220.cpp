/* problem statement text */
/*
CSES - Counting Numbers

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of integers between aaa and bbb where no two adjacent digits are the same.
Input
The only input line has two integers aaa and bbb.
Output
Print one integer: the answer to the problem.
Constraints

0≤a≤b≤10180 \le a \le b \le 10^{18}0≤a≤b≤1018

Example
Input:
123 321

Output:
171
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
 string a,b;
 int dp[19][2][2][10][2];
 int solve(int index,bool up,bool down,int LastDigit,int allZero){
    if(index==a.size())return 1;
    int &res=dp[index][up][down][LastDigit][allZero];
	if(~res)return res;
	res=0;
    int start=(down?0:a[index]-'0');
    int lim=(up?9:b[index]-'0');
    for(int i=start;i<=lim;i++){
        if(!allZero&&i==LastDigit)continue;
		res+=solve(index+1,up||i<b[index]-'0',down||i>a[index]-'0',i,allZero&&i==0);
	}
    return res;	
 }
signed main() {
    khaled
	cin>>a>>b;
	memset(dp,-1,sizeof dp);
	while(a.size()<b.size())a='0'+a;
	cout<<solve(0,false,false,11,true);
}