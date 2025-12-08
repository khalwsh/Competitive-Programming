/* problem statement text */
/*
CSES - Increasing Subsequence II

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to calculate the number of increasing subsequences it contains. If two subsequences have the same values but in different positions in the array, they are counted separately.
Input
The first input line has an integer nnn: the size of the array.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the number of increasing subsequences modulo 109+710^9+7109+7.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
3
2 1 3

Output:
5

Explanation: The increasing subsequences are [2][2][2], [1][1][1], [3][3][3], [2,3][2,3][2,3] and [1,3][1,3][1,3].
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
const int mod = 1e9 + 7;
struct SegmentTree {
    vector<int>tree;
    SegmentTree(int n) {
        tree.resize(4 * n);
    }
    void upd(int node , int nl , int nr , int i , int delta) {
        if (nl == nr && nl == i) {
            tree[node] = (tree[node] + delta) % mod;
            return;
        }
        if (nl > i || nr < i) return;
        int mid = nl + (nr - nl) /2 ;
        upd(2 * node + 1 , nl , mid , i , delta);
        upd(2 * node + 2 , mid + 1 , nr , i ,  delta);
        tree[node] = (tree[2 * node + 1] + tree[2 * node + 2]) % mod;
    }
    int query(int node , int nl , int nr , int l , int r) {
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return 0;
        int mid = nl + (nr - nl) / 2;
        return (query(2 * node + 1 , nl , mid , l , r) + query(2 * node + 2 , mid + 1 , nr , l , r)) % mod;
    }
};
int main(){
    PRE();
    int n; cin >> n;
    vector<int>v(n) , all;
    for (int i = 0;i < n;i++) {
        cin >> v[i];
        all.emplace_back(v[i]);
    }
    all.emplace_back(0);
    sort(all.begin() , all.end());
    all.erase(unique(all.begin() , all.end()) , all.end());
    for (int i = 0;i < n;i++) v[i] = lower_bound(all.begin() , all.end() , v[i]) - all.begin();
 
    int N = all.size() + 5;
    SegmentTree seg(N);
    seg.upd(0 , 0 , N - 1 , 0 , 1);
    vector<int>dp(n);
    for (int i = 0;i < n;i++) {
        dp[i] = seg.query(0 , 0 , N - 1 , 0 , v[i] - 1);
        seg.upd(0 , 0 , N - 1 , v[i] , dp[i]);
    }
    ll res = 0;
    for (int i = 0;i < n;i++) res += dp[i] , res %= mod;
    cout << res << "\n";
}