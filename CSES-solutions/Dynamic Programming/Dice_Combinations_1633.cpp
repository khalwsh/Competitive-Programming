/* problem statement text */
/*
CSES - Dice Combinations

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of ways to construct sum nnn by throwing a dice one or more times. Each throw produces an outcome between 111 and  666.
For example, if n=3n=3n=3, there are 444 ways:

1+1+11+1+11+1+1
1+21+21+2
2+12+12+1
333

Input
The only input line has an integer nnn.
Output
Print the number of ways modulo 109+710^9+7109+7.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
3

Output:
4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 4 , mod = 1e9 + 7;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    dp[0] = 1;
    for(int i = 1;i < N;i++) {
        for(int j = 1;j <= 6;j++) {
            if(i - j >= 0){
                dp[i] += dp[i - j];
                if(dp[i] >= mod)dp[i] -= mod;
            }
        }
    }
    int n;cin>>n;
    cout<<dp[n];
}