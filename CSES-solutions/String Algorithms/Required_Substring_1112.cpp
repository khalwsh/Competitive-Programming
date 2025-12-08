/* problem statement text */
/*
CSES - Required Substring

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to calculate the number of strings of length nnn having a given pattern of length mmm as their substring. All strings consist of characters A–Z.
Input
The first input line has an integer nnn: the length of the final string.
The second line has a pattern of length mmm.
Output
Print the number of strings modulo 109+710^9+7109+7.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
1≤m≤1001 \le m \le 1001≤m≤100

Example
Input:
6
ABCDB

Output:
52

Explanation: The final string will be of the form ABCDBxxx or xxxABCDB where xxx is any character between A–Z.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int n;
string s;
int dp[1002][102];
const int mod = 1e9 + 7;
 
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    cin >> n >> s;
    vector<int> failure(s.size(), 0);
 
    for (int j = 1; j < s.size(); j++) {
        int i = failure[j - 1];
        while (i > 0 && s[i] != s[j])
            i = failure[i - 1];
        if (s[i] == s[j])
            i++;
        failure[j] = i;
    }
 
    int m = s.size();
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    // dp[i][j] : reprsent how many way you can create string of length i matching j-characters from the suffix but don't contain string pattern
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                int nxt = j;
                while (nxt > 0 && s[nxt] != c)
                    nxt = failure[nxt - 1];
                if (s[nxt] == c)
                    nxt++;
                dp[i + 1][nxt] = (dp[i + 1][nxt] + dp[i][j]) % mod;
            }
        }
    }
 
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res = (res + dp[n][i]) % mod;
    }
 
    ll total = binpow(26, n, mod);
    ll answer = (total - res + mod) % mod;
 
    cout << answer << endl;
}