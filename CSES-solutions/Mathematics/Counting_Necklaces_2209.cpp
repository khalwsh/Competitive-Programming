/* problem statement text */
/*
CSES - Counting Necklaces

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to count the number of different necklaces that consist of nnn pearls and each pearl has mmm possible colors.
Two necklaces are considered to be different if it is not possible to rotate one of them so that they look the same.
Input
The only input line has two numbers nnn and mmm: the number of pearls and colors.
Output
Print one integer: the number of different necklaces modulo 109+710^9+7109+7.
Constraints

1≤n,m≤1061 \le n,m \le 10^61≤n,m≤106

Example
Input:
4 3

Output:
24
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
 
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += binpow(m, __gcd(i, n));
        res %= mod;
    }
    cout << res * binpow(n, mod - 2) % mod;
}