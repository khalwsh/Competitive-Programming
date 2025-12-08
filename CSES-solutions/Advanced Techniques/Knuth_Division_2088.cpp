/* problem statement text */
/*
CSES - Knuth Division

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn numbers, your task is to divide it into nnn subarrays, each of which has a single element.
On each move, you may choose any subarray and split it into two subarrays. The cost of such a move is the sum of values in the chosen subarray.
What is the minimum total cost if you act optimally?
Input
The first input line has an integer nnn: the array size. The array elements are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the minimum total cost.
Constraints

1≤n≤50001 \le n \le 50001≤n≤5000
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
5
2 7 3 2 5

Output:
43
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int main() {
    PRE();
    int n; cin >> n;
    vector<vector<ll>> dp(n , vector<ll>(n));
    vector<ll> a(n);
    for (auto &val : a) cin >> val;
    for (int i = 1;i < n;i++) a[i] += a[i - 1];
    vector<vector<int>> opt(n , vector<int>(n));
    auto C = [&](int i, int j)-> ll {
        // Implement cost function C.
        return a[j] - (i == 0 ? 0 : a[i - 1]);
    };
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
        // Initialize dp[i][i] according to the problem
        dp[i][i] = 0;
    }
    for (int i = n-2; i >= 0; i--) {
        for (int j = i+1; j < n; j++) {
            ll mn = 1e18;
            ll cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k;
                    mn = dp[i][k] + dp[k+1][j] + cost;
                }
            }
            dp[i][j] = mn;
        }
    }
    cout << dp[0][n - 1];
}