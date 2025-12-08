/* problem statement text */
/*
CSES - Minimizing Coins

Time limit: 1.00 s
Memory limit: 512 MB

Consider a money system consisting of nnn coins. Each coin has a positive integer value. Your task is to produce a sum of money xxx using the available coins in such a way that the number of coins is minimal.
For example, if the coins are {1,5,7}\{1,5,7\}{1,5,7} and the desired sum is 111111, an optimal solution is 5+5+15+5+15+5+1 which requires 333 coins.
Input
The first input line has two integers nnn and xxx: the number of coins and the desired sum of money.
The second line has nnn distinct integers c1,c2,…,cnc_1,c_2,\dots,c_nc1​,c2​,…,cn​: the value of each coin.
Output
Print one integer: the minimum number of coins. If it is not possible to produce the desired sum, print −1-1−1.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤x≤1061 \le x \le 10^61≤x≤106
1≤ci≤1061 \le c_i \le 10^61≤ci​≤106

Example
Input:
3 11
1 5 7

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 4 , mod = 1e9 + 7;
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    memset(dp , '?' , sizeof dp);
    dp[0] = 0;
    int n;cin>>n;
    int x;cin>>x;
    for(int i = 0;i < n;++i) {
        int y;cin>>y;
        for(int j = 0;j <= x;j++) {
            dp[j + y] = min(dp[j + y] , 1 + dp[j]);
        }
    }
    if(dp[x] >= 1e9)dp[x] = -1;
    cout<<dp[x];
}