/* problem statement text */
/*
CSES - Distinct Subsequences

Time limit: 1.00 s
Memory limit: 512 MB

You are given a string. You can remove any number of characters from it, but you cannot change the order of the remaining characters.
How many different strings can you generate?
Input
The first input line contains a string of size nnn. Each character is one of a–z.
Output
Print one integer: the number of strings modulo 109+710^9+7109+7.
Constraints

1≤n≤5⋅1051 \le n \le 5 \cdot 10^51≤n≤5⋅105

Example
Input:
aybabtu

Output:
103
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
const int mod = 1e9 + 7;
int main() {
    PRE();
    string s; cin >> s;
    int n = (int)s.size();
    vector<ll> dp(n+1, 0);
    dp[0] = 1;
    vector<int> last(256, 0);
    for (int i = 1; i <= n; ++i) {
        auto ch = s[i-1];
        dp[i] = dp[i-1] * 2ULL;
        if (last[ch] != 0) {
            dp[i] -= dp[last[ch] - 1];
        }
        dp[i] %= mod;
        dp[i] += mod;
        dp[i] %= mod;
        last[ch] = i;
    }
    cout << (dp[n] - 1 + mod) % mod;
}