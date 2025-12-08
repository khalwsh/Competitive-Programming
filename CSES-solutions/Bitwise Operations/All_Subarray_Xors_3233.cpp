/* problem statement text */
/*
CSES - All Subarray Xors

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find all integers that are the xor sum in some subarray.
Input
The first line has an integer nnn: the size of the array.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
First print an integer kkk: the number of distinct integers that are the xor sum in some subarray.
After this print kkk integers: the xor sums in increasing order.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤xi≤1060 \le x_i \le 10^60≤xi​≤106

Example
Input:
4
5 1 5 9

Output:
7
1 4 5 8 9 12 13
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
#define int ll
int add(int a, int b) {
    return (a + b);
}
 
int sub(int a, int b) {
    return (a - b);
}
 
void fwht(vector<ll> &a, int inv, int f) {
    int sz = a.size();
    for (int len = 1; 2 * len <= sz; len <<= 1) {
        for (int i = 0; i < sz; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int x = a[i + j];
                int y = a[i + j + len];
 
                if (f == 0) {
                    if (!inv)  a[i + j] = y, a[i + j + len] = add(x,  y);
                    else  a[i + j] = sub(y, x), a[i + j + len] = x;
                }
                else if (f == 1) {
                    if (!inv)  a[i + j + len] = add(x, y);
                    else  a[i + j + len] = sub(y, x);
                }
                else {
                    a[i + j] = add(x, y);
                    a[i + j + len] = sub(x, y);
                }
            }
        }
    }
}
// for example to get all pairs xor send a and b as the frequency array of values
vector<ll> mul(vector<ll> a, vector<ll> b, int f) { // 0:AND, 1:OR, 2:XOR
    int sz = a.size();
    fwht(a, 0, f);  fwht(b, 0, f);
    vector<ll> c(sz);
    for (int i = 0; i < sz; ++i) {
        c[i] = a[i] * b[i];
    }
    fwht(c, 1, f);
    if (f == 2) {
        for (int i = 0; i < sz; ++i) {
            c[i] = c[i] / sz;
        }
    }
    return c;
}
const int N = 1 << 20;
vector<ll> a(N);
signed main() {
    PRE();
    int n; cin >> n;
    vector<ll>v;
    for (int i = 0;i < n;i++) {
        int x; cin >> x;
        v.emplace_back(x);
    }
    for (int i = 1;i < n;i++) v[i] ^= v[i - 1];
    a[0]++;
    vector<int>res;
    for (int i = 0;i < n;i++) {
        a[v[i]]++;
        if (a[v[i]] > 1 && res.empty()) res.emplace_back(0);
    }
    auto r = mul(a , a , 2);
    for (int i = 1;i < 1 << 20;i++) {
        if (r[i]) {
            res.emplace_back(i);
        }
    }
    cout << res.size() << '\n';
    for (auto &val : res) cout << val << " ";
}