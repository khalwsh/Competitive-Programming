/* problem statement text */
/*
CSES - Divisor Analysis

Time limit: 1.00 s
Memory limit: 512 MB

Given an integer, your task is to find the number, sum and product of its divisors. As an example, let us consider the number 121212:

the number of divisors is 666 (they are 111, 222, 333, 444, 666, 121212)
the sum of divisors is 1+2+3+4+6+12=281+2+3+4+6+12=281+2+3+4+6+12=28
the product of divisors is 1⋅2⋅3⋅4⋅6⋅12=17281 \cdot 2 \cdot 3 \cdot 4 \cdot 6 \cdot 12 = 17281⋅2⋅3⋅4⋅6⋅12=1728

Since the input number may be large, it is given as a prime factorization.
Input
The first line has an integer nnn: the number of parts in the prime factorization.
After this, there are nnn lines that describe the factorization. Each line has two numbers xxx and kkk where xxx is a prime and kkk is its power.
Output
Print three integers modulo 109+710^9+7109+7: the number, sum and product of the divisors.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
2≤x≤1062 \le x \le 10^62≤x≤106
each xxx is a distinct prime
1≤k≤1091 \le k \le 10^91≤k≤109

Example
Input:
2
2 2
3 1

Output:
6 28 1728
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
 
const ll MOD = 1000000007LL;
const ll MOD1 = 1000000006LL;
 
ll modpow(ll a, ll b, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = ( (__int128)res * a ) % mod;
        a = ( (__int128)a * a ) % mod;
        b >>= 1;
    }
    return res;
}
 
ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}
 
ll countDivisors(const vector<pair<ll,ll>>& factors) {
    ll ans = 1;
    for (auto &p : factors) {
        ll k = p.second;
        ans = (ans * ((k + 1) % MOD)) % MOD;
    }
    return ans;
}
ll sumDivisors(const vector<pair<ll,ll>>& factors) {
    ll ans = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        if (x == 1) {
            ans = (ans * ((k + 1) % MOD)) % MOD;
        } else {
            ll numerator = (modpow(x, k + 1, MOD) - 1 + MOD) % MOD;
            ll denom_inv = modinv((x - 1 + MOD) % MOD, MOD);
            ll term = ( (__int128)numerator * denom_inv ) % MOD;
            ans = (ans * term) % MOD;
        }
    }
    return ans;
}
 
ll productDivisors(const vector<pair<ll,ll>>& orig_factors) {
    vector<pair<ll,ll>> factors = orig_factors;
    ll num1 = 1;
    bool halvedOne = false;
    for (auto &p : factors) {
        ll k = p.second;
        if (!halvedOne && (k % 2 == 1)) {
            num1 = (num1 * (( (k + 1) / 2 ) % MOD1)) % MOD1;
            halvedOne = true;
        } else {
            num1 = (num1 * ((k + 1) % MOD1)) % MOD1;
        }
    }
    if (!halvedOne) {
        for (auto &p : factors) p.second /= 2;
    }
    ll number = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        number = ( (__int128)number * modpow(x, k, MOD) ) % MOD;
    }
    ll prod = modpow(number, num1, MOD);
    return prod;
}
 
int main() {
    PRE();
    int n;
    cin >> n;
    vector<pair<ll,ll>> factors;
    for (int i = 0; i < n; ++i) {
        ll x, k;
        cin >> x >> k;
        factors.emplace_back(x, k);
    }
 
    ll num = countDivisors(factors);
    ll sum = sumDivisors(factors);
    ll prod = productDivisors(factors);
 
    cout << num << " " << sum << " " << prod << "\n";
}