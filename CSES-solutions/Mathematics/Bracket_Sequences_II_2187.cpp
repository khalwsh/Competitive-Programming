/* problem statement text */
/*
CSES - Bracket Sequences II

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to calculate the number of valid bracket sequences of length nnn when a prefix of the sequence is given.
Input
The first input line has an integer nnn.
The second line has a string of kkk characters: the prefix of the sequence.
Output
Print the number of sequences modulo 109+710^9+7109+7.
Constraints

1≤k≤n≤1061 \le k \le n \le 10^61≤k≤n≤106

Example
Input:
6
(()

Output:
2

Explanation: There are two possible sequences: (())() and (()()).
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-9;
#define int long long
template<typename T>
using ordered_set=tree<T,null_type,greater_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool line_checking(long long a1,long long b1,long long a2,long long b2,long long a3,long long b3){return (a3-a1)*(b2-b1)==(a2-a1)*(b3-b1);}
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long safe_mul_mod(long long a,long long b,const long long &mod){long long res=0,y=a%mod;while(b>0){if(b&1){res=((res%mod)+(y%mod))%mod;}y=((y%mod)*(2ll%mod))%mod;b>>=1;}return (res%mod);}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
long long mod_inverse_fermat(long long B,const long long&mod){ return fast_power(B,mod-2,mod);}//mod is prime
vector<int>mod_inverse_for_range(int n,int p){vector<int>inv(n+1,1);for(int i=2;i<=n;i++) {inv[i] = ( p - (p / i) * inv[p % i] % p ) % p;}return inv;}//mod is prime
vector<long long>factorial(long long n,const long long& mod){vector<long long>v(n+1,1);for(int i=2;i<=n;i++)v[i]=mul(i,v[i-1],mod);return v;}
long long phi(long long n) {long long result = n;for (int i = 2; i * i <= n; i++) {if (n % i == 0) {while (n % i == 0)n /= i;result -= result / i;}}if (n > 1)result -= result / n;return result;}
bool power_of_two(int n) { n=abs(n); return n && !(n & (n - 1));}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;}
const int N=2e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=6e18;
//__builtin_clzll(x): the number of zeros at the beginning of the number
//__builtin_ctzll(x): the number of zeros at the end of the number
//__builtin_popcountll(x): the number of ones in the number
//__builtin_parityll(x): the parity (even or odd) of the number of ones
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
int nCr(vector<int>&fact,int n,int r){
    if(r>n)return 0;
    return mul(fact[n],mul(fast_power(fact[r],mod-2,mod), fast_power(fact[n-r],mod-2,mod),mod),mod);
 
}
signed main() {
    khaled
    int n;
    cin>>n;
    vector<int>fact=factorial(n,mod);
    string s;
    cin>>s;
    if(s.size()==n){
        stack<char>sk;
        for(auto &val:s){
            if(sk.empty()||val=='(')sk.push('(');
            else if(val==')')sk.pop();
        }
        cout<<(sk.empty()?1:0)<<line;
        return 0;
    }
    if(n&1||count(s.begin(),s.end(),'(')>n/2||count(s.begin(),s.end(),')')>n/2){
        cout<<0;
        return 0;
    }
    int cur_location=0;
    for(auto &val:s){
        cur_location+=(val=='('?1:-1);
        if(cur_location<0){
            cout<<0;
            return 0;
        }
    }
    if(count(s.begin(),s.end(),'(')==n/2&&s.size()!=n){
        cout<<1<<line;
        return 0;
    }
    int x=(int)s.size();
    int y=cur_location;
    int inv_y=-1-abs(y+1);
    //cout<<x<<" "<<y<<" "<<x<<" "<<inv_y<<line;
    cout<<add(nCr(fact,n-x,(n-x-y)/2),-nCr(fact,n-x,(n-x+inv_y)/2),mod);
}