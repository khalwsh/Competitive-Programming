/* problem statement text */
/*
CSES - Chessboard and Queens

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to place eight queens on a chessboard so that no two queens are attacking each other. As an additional challenge, each square is either free or reserved, and you can only place queens on the free squares. However, the reserved squares do not prevent queens from attacking each other.
How many possible ways are there to place the queens?
Input
The input has eight lines, and each of them has eight characters. Each square is either free (.) or reserved (*).
Output
Print one integer: the number of ways you can place the queens.
Example
Input:
........
........
..*.....
........
........
.....**.
...*....
........

Output:
65
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
long double NCR_LINEAR_TIME(long long n,long long r){if(r>n)return 0;if(r==0||r==n){return 1;}if(r==1||r==n-1)return n;return NCR_LINEAR_TIME(n-1,r-1)*(long double)n/r;}
bool power_of_two(int n) { n=abs(n);  return n && !(n & (n - 1));}
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
int n=8;
vector<vector<char>>v(n,vector<char>(n));
int colo_check[120];
int diag1[120];
int diag2[120];
int row_check[120];
bool flag=false;
vector<vector<vector<char>>>res;
void chessboard(int colomn,int counter)
{
    if(!flag) {
        if(counter==n)
            res.emplace_back(v);
        if (colomn == n || counter == n)
            return;
        for (int row = 0; row < n; row++) {
            int x=row,y=colomn;
            if (v[row][colomn] != 1&&!row_check[row]&&!colo_check[colomn]&&!diag1[x+y] && !diag2[x-y+n-1]) {
                v[row][colomn] = 'Q';
                colo_check[colomn]=1;
                row_check[row]=1;
                diag1[x+y]=1;
                diag2[x-y+n-1]=1;
                //if (check()) {
                chessboard(colomn + 1, counter + 1);
                v[row][colomn] = '.';
                chessboard(colomn + 1, counter);
                colo_check[colomn]=0;
                row_check[row]=0;
                diag1[x+y]=0;
                diag2[x-y+n-1]=0;
            }
        }
    }
}
signed main() {
    khaled
    vector<vector<char>>org;
    for(auto &val:v){
        for(auto &i:val)
            cin>>i;
    }
    org=v;
    chessboard(0,0);
    int cnt=res.size();
    for(auto &val:res){
        bool fail=false;
        for(int i=0;i<val.size();i++){
            for(int j=0;j<val[i].size();j++){
                if(org[i][j]=='*'&&val[i][j]=='Q')fail=true;
                if(fail)break;
            }
            if(fail)break;
        }
        if(fail)cnt--;
    }
    cout<<cnt;
}