/* problem statement text */
/*
CSES - Counting Bits

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of one bits in the binary representations of integers between 111 and nnn.
Input
The only input line has an integer nnn.
Output
Print the number of one bits in the binary representations of integers between 111 and nnn.
Constraints

1≤n≤10151 \le n \le 10^{15}1≤n≤1015

Example
Input:
7

Output:
12

Explanation: The binary representations of 1…71 \ldots 71…7 are 1, 10, 11, 100, 101, 110, and 111, so there are a total of 12 one bits.
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
    ll n;cin >> n;
    ll res = 0;
    for (int i = 0; i < 60; i++) {
        ll bit = 1LL << i;
        ll cycle = bit << 1;
 
        ll full = n / cycle;
        ll rem = n % cycle;
 
        res += full * bit;
        res += max(0LL, rem - bit + 1);
    }
    cout << res << '\n';
}