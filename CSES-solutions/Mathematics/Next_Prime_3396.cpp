/* problem statement text */
/*
CSES - Next Prime

Time limit: 1.00 s
Memory limit: 512 MB

Given a positive integer nnn, find the next prime number after it.
Input
The first line has an integer ttt: the number of tests.
After that, each line has a positive integer nnn.
Output
For each test, print the next prime after nnn.
Constraints

1≤t≤201 \le t \le 201≤t≤20
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
2
3
5
43
1361
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
using u64 = uint64_t;
using u128 = __uint128_t;
 
u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}
 
bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
bool MillerRabin(u64 n) {
    if (n < 2)
        return false;
 
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
 
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
int main() {
    PRE();
    int t;cin >> t;
    while (t--) {
        ll n;cin >> n;
        n++;
        while (!MillerRabin(n))n++;
        cout << n << '\n';
    }
}