/* problem statement text */
/*
CSES - Hamiltonian Flights

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm flight connections between them. You want to travel from Syrjälä to Lehmälä so that you visit each city exactly once. How many possible routes are there?
Input
The first input line has two integers nnn and mmm: the number of cities and flights. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n. City 111 is Syrjälä, and city nnn is Lehmälä.
Then, there are mmm lines describing the flights. Each line has two integers aaa and bbb: there is a flight from city aaa to city bbb. All flights are one-way flights.
Output
Print one integer: the number of routes modulo 109+710^9+7109+7.
Constraints

2≤n≤202 \le n \le 202≤n≤20
1≤m≤n21 \le m \le n^21≤m≤n2
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 6
1 2
1 3
2 3
3 2
2 4
3 4

Output:
2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 21 , mod = 1e9 + 7;
int n , m;
vector<int>adj[N];
 
int dp[N][1 << N];
 
 
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int a , b;cin >> a >> b;a-- , b--;
        adj[a].emplace_back(b);
    }
    dp[0][1] = 1;
    // 2 ^ 20 * n * n * n
    // 8000 * 2 ^ 20
    // 8e3 * 1e6 -> 8e9
    for (int i = 1;i < 1 << n; i++) {
        if (__builtin_popcount(i) != n && (i >> (n - 1) & 1))continue;
        for (int j = 0;j < n;j++) {
            if (!(i >> j & 1)) continue;
            for (auto &k : adj[j]) {
                if (i >> k & 1)continue;
                if (k == n - 1 && __builtin_popcount(i | (1 << k)) != n)continue;
                dp[k][i | (1 << k)] += dp[j][i];
                if (dp[k][i | (1 << k)] >= mod)
                    dp[k][i | (1 << k)] -= mod;
            }
        }
    }
    cout << dp[n - 1][(1 << n) - 1] << '\n';
}