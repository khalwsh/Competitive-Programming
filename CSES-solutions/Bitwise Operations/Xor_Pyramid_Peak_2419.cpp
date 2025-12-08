/* problem statement text */
/*
CSES - Xor Pyramid Peak

Time limit: 1.00 s
Memory limit: 512 MB

Consider a xor pyramid where each number is the xor of lower-left and lower-right numbers. Here is an example pyramid:

Given the bottom row of the pyramid, your task is to find the topmost number.
Input
The first line has an integer nnn: the size of the pyramid.
The next line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the bottom row of the pyramid.
Output
Print one integer: the topmost number.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ai≤1091 \le a_i \le 10^91≤ai​≤109

Example
Input:
8
2 10 5 12 9 5 1 5

Output:
9
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
bool Ncr(int n , int i) {
    // Ncr(n , i) % 2 = 1 if every bit of i is less than or equal to the corresponding bit of n
    return !(i & ~(n - 1));
}
int main() {
    PRE();
    int n; cin >> n;
    ll res = 0;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        if (Ncr(n , i)) res ^= x;
    }
    cout << res;
}