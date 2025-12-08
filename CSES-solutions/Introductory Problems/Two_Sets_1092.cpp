/* problem statement text */
/*
CSES - Two Sets

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to divide the numbers 1,2,…,n1,2,\ldots,n1,2,…,n into two sets of equal sum.
Input
The only input line contains an integer nnn.
Output
Print "YES", if the division is possible, and "NO" otherwise.
After this, if the division is possible, print an example of how to create the sets. First, print the number of elements in the first set followed by the elements themselves in a separate line, and then, print the second set in a similar way.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example 1
Input:
7

Output:
YES
4
1 2 4 7
3
3 5 6
Example 2
Input:
6

Output:
NO
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
vector<vector<long long>>dp_nCr(100,vector<long long>(100,-1));
long long nCr(long long n,long long r){if(r == 0 || r == n)return 1;if(r == 1 || r == n - 1)return n;if(dp_nCr[n][r]!=-1)return dp_nCr[n][r]; return dp_nCr[n][r]= nCr(n - 1, r) + nCr(n - 1, r - 1);}
long long derangement(int n){if(n == 0)return 1;if(n == 1)return 0;if(n == 2)return 1;return (n - 1)*(derangement(n - 1) + derangement(n - 2));}
bool line_checking(long long a1,long long b1,long long a2,long long b2,long long a3,long long b3){return (a3-a1)*(b2-b1)==(a2-a1)*(b3-b1);}
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long safe_mul_mod(long long a,long long b,const long long &mod){long long res=0,y=a%mod;while(b>0){if(b&1){res=((res%mod)+(y%mod))%mod;}y=((y%mod)*(2ll%mod))%mod;b>>=1;}return (res%mod);}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2,mod);}//mod is prime
vector<int>mod_inverse_for_range(int p){vector<int>inv(p,1);for(int i=2;i<p;i++) {inv[i] = ( p - (p / i) * inv[p % i] % p ) % p;}return inv;}//mod is prime
vector<long long>factorial(long long n,const long long& mod){vector<long long>v(n+1,1);for(int i=2;i<=n;i++)v[i]=mul(i,v[i-1],mod);return v;}
long long NCR_MOD(long long n, long long r,vector<long long>&fact,const long long&mod){return mul(mul(fact[n], mod_inverse_fermat(fact[n - r], mod), mod), mod_inverse_fermat(fact[r], mod), mod);}
long long phi(long long n) {long long result = n;for (int i = 2; i * i <= n; i++) {if (n % i == 0) {while (n % i == 0)n /= i;result -= result / i;}}if (n > 1)result -= result / n;return result;}
vector<long long> segmentedSieve(long long L,long long R) {auto lim = (long long)sqrt(R);vector<bool> mark(lim + 1, false);vector<long long> primes;for (long long i = 2; i <= lim; ++i) {if (!mark[i]) {primes.emplace_back(i);for (long long j = i * i; j <= lim; j += i)     mark[j] = true;}}vector<bool> isPrime(R - L + 1, true);vector<long long>res;for (auto &i : primes)for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)isPrime[j - L] = false;if (L == 1)isPrime[0] = false;for(long long i=L;i<=R;i++){if(isPrime[i-L])res.emplace_back(i);}return res;}
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double Eps=1e-10;
#define int long long
template<typename T>
using ordered_set=tree<T,null_type,greater_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N=1e6;
const int mod=1e9+7;
const long long inf=1e17;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
signed main() {
    khaled
    int n;
    cin>>n;
    if((n*(n+1)/2)&1^1){
        int tar=n*(n+1)/2;
cout<<"YES"<<line;
        tar/=2;
        set<int>s;
        for(int i=1;i<=n;i++)s.insert(i);
        auto it=s.rbegin();
        vector<int>v1;
        while(tar>*it){
            v1.emplace_back(*it);
            tar-=*it;
            s.erase(*it);
            it=s.rbegin();
        }
        v1.emplace_back(*s.lower_bound(tar));
        s.erase(v1.back());
        cout<<v1.size();
        cout<<line;
        for(auto &val:v1)cout<<val<<" ";
        cout<<line;
        cout<<s.size();
        cout<<line;
        for(auto &val:s)
            cout<<val<<" ";
        cout<<line;
    }else{
        cout<<"NO";
    }
}