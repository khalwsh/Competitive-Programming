/* problem statement text */
/*
CSES - Two Sets II

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of ways numbers 1,2,…,n1,2,\ldots,n1,2,…,n can be divided into two sets of equal sum.
For example, if n=7n=7n=7, there are four solutions:

{1,3,4,6}\{1,3,4,6\}{1,3,4,6} and {2,5,7}\{2,5,7\}{2,5,7}
{1,2,5,6}\{1,2,5,6\}{1,2,5,6} and {3,4,7}\{3,4,7\}{3,4,7}
{1,2,4,7}\{1,2,4,7\}{1,2,4,7} and {3,5,6}\{3,5,6\}{3,5,6}
{1,6,7}\{1,6,7\}{1,6,7} and {2,3,4,5}\{2,3,4,5\}{2,3,4,5}

Input
The only input line contains an integer nnn.
Output
Print the answer modulo 109+710^9+7109+7.
Constraints

1≤n≤5001 \le n \le 5001≤n≤500

Example
Input:
7

Output:
4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500 * 500 , mod = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    ll sum = n * (n + 1) / 2;
    if(sum & 1 ) {
        cout<<0<<'\n';
        exit(0);
    }
    vector<int>dp(sum + 1);
    dp[0] = 1;
    for(int i = 1;i <= n;i++) {
        int x;x = i;
        vector<int>ndp(sum + 1);
        for(int j = 0;j <= sum;j++)ndp[j] = dp[j];
        for(int j = 0;j + x <= sum;j++) {
            ndp[j + x] += dp[j];
            if(ndp[j + x] >= mod)ndp[j + x] -= mod;
        }
        swap(dp , ndp);
    }
    cout<<1LL * dp[sum / 2] * 500000004 % mod;
}