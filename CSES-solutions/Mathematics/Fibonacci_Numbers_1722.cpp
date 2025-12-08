/* problem statement text */
/*
CSES - Fibonacci Numbers

Time limit: 1.00 s
Memory limit: 512 MB

The Fibonacci numbers can be defined as follows:

F0=0F_0=0F0​=0
F1=1F_1=1F1​=1
Fn=Fn−2+Fn−1F_n = F_{n-2}+F_{n-1}Fn​=Fn−2​+Fn−1​

Your task is to calculate the value of FnF_nFn​ for a given nnn.
Input
The only input line has an integer nnn.
Output
Print the value of FnF_nFn​ modulo 109+710^9+7109+7.
Constraints

0≤n≤10180 \le n \le 10^{18}0≤n≤1018

Example
Input:
10

Output:
55
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
#define double long double
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N=2e5+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=3e18+1;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
struct Matrix{
    int arr[2][2];
    Matrix(int a=1,int b=1,int c=1,int d=0){
        arr[0][0]=a;
        arr[0][1]=b;
        arr[1][0]=c;
        arr[1][1]=d;
    }
    Matrix operator*(const Matrix & a){
        Matrix res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                int temp = 0;
                for(int k = 0;k<2;k++){
                    temp = add(temp,mul(arr[i][k],a.arr[k][j],mod),mod);
                }
                res.arr[i][j] = temp;
            }
        }
        return res;
    }
};
Matrix MatPow(Matrix base, long long n) {
    Matrix ans (1,0,0,1);
    while (n) {
        if(n&1)
            ans = ans*base;
        base = base*base;
        n >>= 1;
    }
    return ans;
}
long long fib(int n) {
    Matrix base;
    return MatPow(base, n).arr[0][1];
}
signed main() {
    khaled
    int n;
    cin>>n;
    cout<<fib(n)<<line;
}