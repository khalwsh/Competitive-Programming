/* problem statement text */
/*
CSES - Rectangle Cutting

Time limit: 1.00 s
Memory limit: 512 MB

Given an a×ba \times ba×b rectangle, your task is to cut it into squares. On each move you can select a rectangle and cut it into two rectangles in such a way that all side lengths remain integers. What is the minimum possible number of moves?
Input
The only input line has two integers aaa and bbb.
Output
Print one integer: the minimum number of moves.
Constraints

1≤a,b≤5001 \le a,b \le 5001≤a,b≤500

Example
Input:
3 5

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5001;
int a , b;
int dp[501][501];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>a>>b;
    memset(dp , '?' , sizeof dp);
    for(int i = 0;i <= 500;i++)dp[i][i] = 0;
    for(int i = 1;i <= a;i++) {
        for(int j = 1;j <= b;j++) {
            if(i == j)continue;
            for(int k = 1;k < max(i , j);k++) {
                if(k <= i)dp[i][j] = min(dp[i][j] , 1 + dp[i - k][j] + dp[k][j]);
                if(j - k >= 0)dp[i][j] = min(dp[i][j] , 1 + dp[i][j - k] + dp[i][k]);
            }
        }
    }
    cout<<dp[a][b];
}