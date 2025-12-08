/* problem statement text */
/*
CSES - Maximum Xor Subset

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find the maximum xor sum of a subset.
Input
The first line has an integer nnn: the size of the array.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the maximum xor sum of a subset.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109

Example
Input:
4
1 6 12 6

Output:
13
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
struct Basis {
    const static int BITs = 30;
    ll basis[BITs + 1]{};
    int comp_sz = 0;
 
    void insert(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }
 
    ll get(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (msk >> i & 1) continue;
            msk ^= basis[i];
        }
        return msk;
    }
};
int main() {
    PRE();
    Basis bs;
    int n;cin >> n;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        bs.insert(x);
    }
    cout << bs.get(0) << '\n';
}