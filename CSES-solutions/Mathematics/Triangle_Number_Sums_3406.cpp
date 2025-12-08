/* problem statement text */
/*
CSES - Triangle Number Sums

Time limit: 1.00 s
Memory limit: 512 MB

A triangle number is a positive integer of the form 1+2+⋯+k1+2+\dots+k1+2+⋯+k. The first triangle numbers are 111, 333, 666, 101010 and 151515.
Every positive integer can be represented as a sum of triangle numbers. For example, 42=21+2142=21+2142=21+21 and 1337=1326+10+11337=1326+10+11337=1326+10+1.
Given a positive integer nnn, determine the smallest number of triangle numbers that sum to nnn.
Input
The first line has an integer ttt: the number of tests.
After that, each line has a positive integer nnn.
Output
For each test, print the smallest number of triangle numbers.
Constraints

1≤t≤1001 \le t \le 1001≤t≤100
1≤n≤10121 \le n \le 10^{12}1≤n≤1012

Example
Input:
5
1
2
3
42
1337

Output:
1
2
1
2
3
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
 
ll work(ll x) { return x * (x + 1) >> 1; }
 
bool check(ll x) {
    ll p = sqrt(x * 2);
    if (work(p) == x) return 1;
    return 0;
}
 
int main() {
    PRE();
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (check(n)) {
            cout << 1 << '\n';
        } else {
            int ans = 3;
            ll x, m;
            x = m = 2e6;
            for (ll i = 1; i <= m && work(i) <= n; i++) {
                while (work(i) + work(x) > n) x--;
                if (work(i) + work(x) == n) {
                    ans = 2;
                    break;
                }
            }
            cout << ans << '\n';
        }
    }
}