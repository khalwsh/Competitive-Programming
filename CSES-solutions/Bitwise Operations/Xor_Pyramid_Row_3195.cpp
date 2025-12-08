/* problem statement text */
/*
CSES - Xor Pyramid Row

Time limit: 1.00 s
Memory limit: 512 MB

Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers. Here is an example pyramid:

Given the bottom row of the pyramid, your task is to find the numbers on the kkk-th row from the top.
Input
The first line has two integers nnn and kkk: the size of the pyramid and the given row.
The next line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the bottom row of the pyramid.
Output
Print kkk integers: the numbers on the kkk-th row from the top.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤ai≤1091 \le a_i \le 10^91≤ai​≤109

Example
Input:
8 5
2 10 5 12 9 5 1 5

Output:
1 10 5 1 8
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
 
int main() {
    PRE();
    int n; cin >> n;
    int k; cin >> k;
    vector<int>dp(n);
    k = n - k;
    for (int i = 0;i < n;i++) cin >> dp[i];
    for (int i = 0;i < 20;i++) {
        if (k >> i & 1) {
            for (int j = 0;j < (n - (1 << i));j++) {
                dp[j] ^= dp[j + (1 << i)];
            }
        }
    }
    for (int i = 0;i < n - k;++i) cout << dp[i] << " ";
}