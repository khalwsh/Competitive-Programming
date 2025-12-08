/* problem statement text */
/*
CSES - Counting Tilings

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of ways you can fill an n×mn \times mn×m grid using 1×21 \times 21×2 and 2×12 \times 12×1 tiles.
Input
The only input line has two integers nnn and mmm.
Output
Print one integer: the number of ways modulo 109+710^9+7109+7.
Constraints

1≤n≤101 \le n \le 101≤n≤10
1≤m≤10001 \le m \le 10001≤m≤1000

Example
Input:
4 7

Output:
781
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n , m;
vector<int>adj[(1<<10 )+ 1];
bool can(int a, int b) {
    if(a & b)return false;
    int x = ((~a & ~b) & ((1<<n) - 1));
    if(x % 3 != 0)return false;
    int y = x / 3;
    return (y & (y<<1)) == 0;
}
const int mod = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n>>m;
    for(int i = 0;i < (1<<n);i++) {
        for(int j = 0;j < (1<<n);j++) {
            if(can(i , j))adj[i].emplace_back(j);
        }
    }
    ll dp[m + 1][1<<n];
    memset(dp ,0 , sizeof dp);
    dp[0][0] = 1;
    for(int i = 1;i <= m;i++) {
        for(int j = 0;j < (1<<n);j++) {
            for(auto &val:adj[j])dp[i][j] += dp[i - 1][val] , dp[i][j] %= mod;
        }
    }
    cout<<dp[m][0]<<'\n';
}