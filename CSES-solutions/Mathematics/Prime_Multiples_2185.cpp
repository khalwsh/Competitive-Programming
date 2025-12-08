/* problem statement text */
/*
CSES - Prime Multiples

Time limit: 1.00 s
Memory limit: 512 MB

You are given kkk distinct prime numbers a1,a2,…,aka_1,a_2,\ldots,a_ka1​,a2​,…,ak​ and an integer nnn.
Your task is to calculate how many of the first nnn positive integers are divisible by at least one of the given prime numbers.
Input
The first input line has two integers nnn and kkk.
The second line has kkk prime numbers a1,a2,…,aka_1,a_2,\ldots,a_ka1​,a2​,…,ak​.
Output
Print one integer: the number integers within the interval 1,2,…,n1,2,\ldots,n1,2,…,n that are divisible by at least one of the prime numbers.
Constraints

1≤n≤10181 \le n \le 10^{18}1≤n≤1018
1≤k≤201 \le k \le 201≤k≤20
2≤ai≤n2 \le a_i \le n2≤ai​≤n

Example
Input:
20 2
2 5

Output:
12

Explanation: the 121212 numbers are 2,4,5,6,8,10,12,14,15,16,18,202,4,5,6,8,10,12,14,15,16,18,202,4,5,6,8,10,12,14,15,16,18,20.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
const int C = 21;
ull binom[C][C];
void init() {
    for(int i = 0; i < C; i++)
        binom[i][0] = binom[i][i] = 1;
    for(int i = 2; i < C; i++)
        for(int j = 1; j < i; j++)
            binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
 
}
// calc(elements count , subset size , upper bound , elements)
// call init first
ll calc(ull n , ull m , ull y , vector<ull> &a) {
    ull ans = 0;
    for(ull msk = 0; msk < (1 << n); msk++) {
        if (popcount(msk) < m) continue;
        ull L = 1;
        for(int i = 0; i < n; i++) {
            if (~msk >> i & 1) continue;
            ull g = gcd(L, a[i]);
            if ((__int128)(L) * a[i] / g > y) L = y + 1;
            else L *= a[i] / g;
        }
        if (popcount(msk) % 2 == m % 2)
            ans += (y / L) * binom[popcount(msk)][m];
        else
            ans -= (y / L) * binom[popcount(msk)][m];
    }
 
    return ans;
}
int main() {
    PRE();
    ll res = 0;
    ll n , k; cin >> n >> k;
    vector<ull> a(k);
    for (int i = 0;i < k;i++) cin >> a[i];
    init();
    for (int i = 1;i <= k;i++) {
        res += calc(k , i , n , a);
    }
    cout << res << '\n';
}