/* problem statement text */
/*
CSES - Xor Pyramid Diagonal

Time limit: 1.00 s
Memory limit: 512 MB

Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers. Here is an example pyramid:

Given the bottom row of the pyramid, your task is to find the leftmost number of each row.
Input
The first line has an integer nnn: the size of the pyramid.
The next line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the bottom row of the pyramid.
Output
Print nnn integers: the leftmost numbers of the rows from bottom to top.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ai≤1091 \le a_i \le 10^91≤ai​≤109

Example
Input:
8
2 10 5 12 9 5 1 5

Output:
2 8 7 1 11 4 15 9
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
void forward1(vector<int> &dp , const int BITS) {
    for (int i = 0; i < BITS; i++) {
        for (int j = 1;j < dp.size();j++) {
            if (j & (1 << i))
                dp[j] ^= dp[j ^ (1 << i)];
        }
    }
}
int main() {
    PRE();
    int n;cin >> n;
    vector<int>dp(n);
    for (int i = 0;i < n;i++) cin >> dp[i];
    forward1(dp , 20);
    for (int i = 0;i < n;++i) cout << dp[i] << " ";
}