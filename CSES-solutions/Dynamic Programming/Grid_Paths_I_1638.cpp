/* problem statement text */
/*
CSES - Grid Paths I

Time limit: 1.00 s
Memory limit: 512 MB

Consider an n×nn \times nn×n grid whose squares may have traps. It is not allowed to move to a square with a trap.
Your task is to calculate the number of paths from the upper-left square to the lower-right square. You can only move right or down.
Input
The first input line has an integer nnn: the size of the grid.
After this, there are nnn lines that describe the grid. Each line has nnn characters: . denotes an empty cell, and * denotes a trap.
Output
Print the number of paths modulo 109+710^9+7109+7.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000

Example
Input:
4
....
.*..
...*
*...

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e3 + 1;
char grid[N][N];
int dp[N][N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    int n;cin>>n;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++)
            cin>>grid[i][j];
    }
    dp[0][0] = 1;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            if(!i && !j || grid[i][j] == '*')continue;
            if(i)dp[i][j] += dp[i - 1][j];
            if(dp[i][j] >= mod)dp[i][j] -= mod;
            if(j)dp[i][j] += dp[i][j - 1];
            if(dp[i][j] >= mod)dp[i][j] -= mod;
        }
    }
    if(grid[0][0] == '*')dp[n - 1][n - 1] = 0;
    cout<<dp[n - 1][n - 1];
}