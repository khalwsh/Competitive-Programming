/* problem statement text */
/*
CSES - K Subset Xors

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Consider the xors of all 2n2^n2n subsets of the array (including the empty subset with xor equal to zero).
Your task is to find the kkk smallest subset xors.
Input
The first line has two integers nnn and kkk: the size of the array and the number of subset xors kkk.
The next line has nnn integers x1,x2,…,xnx_1, x_2,\dots, x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print kkk integers: the kkk smallest subset xors in increasing order.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤k≤min⁡(2n,2⋅105)1 \le k \le \min(2^n, 2 \cdot 10^5)1≤k≤min(2n,2⋅105)
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109

Example
Input:
4 9
3 5 14 8

Output:
0 0 3 3 5 5 6 6 8
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
int n;
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
    ll get(ll k, int n) {
        // k: 1-based index among ALL subsets (duplicates allowed)
        // n: original number of vectors (so total subsets = 1<<n)
        ll mult = 1LL << (n - comp_sz);
        ll k_unique = (k + mult - 1) / mult;
 
        vector<pair<int, ll>> vec;
        for (int i = BITs; i >= 0; --i) {
            if (basis[i]) vec.emplace_back(i, basis[i]);
        }
        int m = (int)vec.size();
        ll rem = k_unique;
        ll x = 0;
        for (int j = 0; j < m; ++j) {
            int lead = vec[j].first;
            ll b = vec[j].second;
            ll half = 1LL << (m - j - 1);
            if (((x >> lead) & 1LL) == 0) {
                if (rem > half) {
                    rem -= half;
                    x ^= b;
                }
            } else {
                if (rem <= half) {
                    x ^= b;
                } else {
                    rem -= half;
                }
            }
        }
        return x;
    }
 
};
int main() {
    PRE();
    Basis bs;
    cin >> n;
    int k; cin >> k;
    for (int i = 0;i < n;i++) {
        int x;cin >> x;
        bs.insert(x);
    }
    for (int i = 1;i <= k;i++) cout << bs.get(i , n) << " ";
}