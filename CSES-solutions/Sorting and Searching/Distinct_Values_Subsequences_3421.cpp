/* problem statement text */
/*
CSES - Distinct Values Subsequences

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, count the number of subsequences where each element is dictinct.
A subsequence is a sequence of array elements from left to right that may have gaps.
Input
The first line has an integer nnn: the array size.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array contents.
Output
Print the number of subsequences with distinct elements. The answer can be large, so print it modulo 109+710^9+7109+7.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
4
1 2 1 3

Output:
11

Explanation: The subsequences are [1][1][1] (two times), [2][2][2], [3][3][3], [1,2][1,2][1,2], [1,3][1,3][1,3] (two times), [2,1][2,1][2,1], [2,3][2,3][2,3], [1,2,3][1,2,3][1,2,3] and [2,1,3][2,1,3][2,1,3].
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 2e5 + 10 , mod = 1e9 + 7;
ll inv[N] , FInv[N] , fact[N];
void Inverse() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
void FactorialInverse() {
    FInv[0] = FInv[1] = 1;
    for (int i = 2; i < N; i++)
        FInv[i] = (inv[i] * FInv[i - 1]) % mod;
}
void factorial() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
}
int Ncr(int n, int r) {
    if(r > n)return 0;
    ll ans = ((fact[n] * FInv[r])
               % mod * FInv[n - r])
              % mod;
    return ans;
}
void init() {
    Inverse();
    FactorialInverse();
    factorial();
}
int main(){
    PRE();
    init();
    int n;cin >> n;
    vector<int>v(n);
    map<int ,int>freq;
    for (auto &val : v) cin >> val , freq[val]++;
    int res = 1;
    for (auto &[v , f] : freq) {
        res = 1LL * res * (Ncr(f , 1) + 1) % mod;
    }
    res = (res - 1 + mod) % mod;
    cout << res << "\n";
}