/* problem statement text */
/*
CSES - Number of Subset Xors

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find the number of different subset xors.
Input
The first line has an integer nnn: the size of the array.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the number of different subset xors.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109

Example
Input:
3
3 6 5

Output:
4

Explanation: The following values can be the xor of a subset:

0=xor of the empty set0 = \text{xor of the empty set}0=xor of the empty set
3=33 = 33=3
5=3⊕65 = 3 \oplus 65=3⊕6
6=3⊕56 = 3 \oplus 56=3⊕5

In this case, no other values can be the xor of a subset.
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
    static const int BITs = 60;
    ll basis[BITs + 1]{};
    int comp_sz = 0;
    void insert(ll msk) {
        for (int i = BITs; i >= 0;i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }
    ll distinct_subsets() {
        return (1LL << comp_sz);
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
    cout << bs.distinct_subsets() << '\n';
}