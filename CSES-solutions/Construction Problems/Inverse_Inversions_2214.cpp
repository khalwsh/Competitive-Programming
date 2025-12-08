/* problem statement text */
/*
CSES - Inverse Inversions

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to create a permutation of numbers 1,2,…,n1,2,\dots,n1,2,…,n that has exactly kkk inversions.
An inversion is a pair (a,b)(a,b)(a,b) where a<ba<ba<b and pa>pbp_a>p_bpa​>pb​ where pip_ipi​ denotes the number at position iii in the permutation.
Input
The only input line has two integers nnn and kkk.
Output
Print a line that contains the permutation. You can print any valid solution.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106
0≤k≤n(n−1)20 \le k \le \frac{n(n-1)}{2}0≤k≤2n(n−1)​

Example
Input:
5 4

Output:
1 5 2 4 3
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
 
int main() {
    PRE();
    ll n , k ; cin >> n >> k;
    vector<int> res(n);
    int l = 1 , r = n;
    for (int i = 0;i < n;i++) {
        if (k >= n - 1 - i) res[i] = r-- , k -= n - 1 - i;
        else res[i] = l++;
    }
    assert(!k);
    for (auto &val  : res) cout << val << " ";
}