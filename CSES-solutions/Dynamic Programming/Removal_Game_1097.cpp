/* problem statement text */
/*
CSES - Removal Game

Time limit: 1.00 s
Memory limit: 512 MB

There is a list of nnn numbers and two players who move alternately. On each move, a player removes either the first or last number from the list, and their score increases by that number. Both players try to maximize their scores.
What is the maximum possible score for the first player when both players play optimally?
Input
The first input line contains an integer nnn: the size of the list.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the list.
Output
Print the maximum possible score for the first player.
Constraints

1≤n≤50001 \le n \le 50001≤n≤5000
−109≤xi≤109-10^9 \le x_i \le 10^9−109≤xi​≤109

Example
Input:
4
4 5 1 3

Output:
8
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n , arr[5001];
const int N = 5001;
ll dp[N][N][2];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>arr[i];
    for(int i = 0;i < n;i++)for(int j = 0;j < n;j++) {
        dp[i][j][0] = 0;
        dp[i][j][1] = 1e15;
    }
    for(int i = 0;i < n;i++) {
        dp[i][i][0] = arr[i];
        dp[i][i][1] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j][0] = max(
                arr[i] + dp[i + 1][j][1],
                arr[j] + dp[i][j - 1][1]
            );
 
            dp[i][j][1] = min(
                dp[i + 1][j][0],
                dp[i][j - 1][0]
            );
        }
    }
    // cout<<dp[0][n - 1][0]<<"\n";
    cout<<dp[0][n - 1][0]<<"\n";
}