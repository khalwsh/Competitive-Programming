/* problem statement text */
/*
CSES - Maximum Subarray Sum

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find the maximum sum of values in a contiguous, nonempty subarray.
Input
The first input line has an integer nnn: the size of the array.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Output
Print one integer: the maximum subarray sum.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤xi≤109-10^9 \le x_i \le 10^9−109≤xi​≤109

Example
Input:
8
-1 3 -2 5 3 -5 2 2

Output:
9
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &mod=INT64_MAX){
    if(power==0)return 1ll;long long d= fast_power(base,power/2)%mod;d=mul(d,d,mod);if(power&1)return mul(d,base,mod);else return d;}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2);}//mod is prime
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
signed main() {
    khaled
    long long res=INT_MIN;
    long long sum=0;
    int n;
    cin>>n;
    vector<long long>v(n);
    for(auto &val:v)
    {
        cin>>val;
        sum=max(val,val+sum);
        res=max(res,sum);
    }
 
    cout<<res<<line;
}
 
 