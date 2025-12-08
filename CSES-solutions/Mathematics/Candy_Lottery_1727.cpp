/* problem statement text */
/*
CSES - Candy Lottery

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn children, and each of them independently gets a random integer number of candies between 111 and kkk.
What is the expected maximum number of candies a child gets?
Input
The only input line contains two integers nnn and kkk.
Output
Print the expected number rounded to six decimal places (rounding half to even).
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤k≤1001 \le k \le 1001≤k≤100

Example
Input:
2 3

Output:
2.444444
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
 
ld dp[101][101];
int vis[101][101];
ll n, k;
 
ld solve(int index, int mx) {
    if (index == n)
        return mx;
    if (vis[index][mx])
        return dp[index][mx];
    vis[index][mx] = 1;
 
    ld res = 0;
    for (int i = 1; i <= k; i++) {
        res += solve(index + 1, max(i, mx)) * (ld)1.0 / k;
    }
    return dp[index][mx] = res;
}
 
int main() {
    PRE();
    cin >> n >> k;
    ld ans = solve(0, 0);
    ld temp = ans * 1e7;
    if ((ll)temp % 10 == 5) {
        if (((ll)(temp / 10) % 10) & 1 ^ 1) {
 
        }else {
            ans = roundl(ans * (ld)1e6) / (ld)1e6;
        }
    }
    cout << fixed << setprecision(6) << ans << '\n';
}