/* problem statement text */
/*
CSES - List Removals

Time limit: 1.00 s
Memory limit: 512 MB

You are given a list consisting of nnn integers. Your task is to remove elements from the list at given positions, and report the removed elements.
Input
The first input line has an integer nnn: the initial size of the list. During the process, the elements are numbered 1,2,…,k1,2,\dots,k1,2,…,k where kkk is the current size of the list.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the list.
The last line has nnn integers p1,p2,…,pnp_1,p_2,\dots,p_np1​,p2​,…,pn​: the positions of the elements to be removed.
Output
Print the elements in the order they are removed.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤pi≤n−i+11 \le p_i \le n-i+11≤pi​≤n−i+1

Example
Input:
5
2 6 1 4 2
3 1 3 1 1

Output:
1 2 2 6 4

Explanation: The contents of the list are [2,6,1,4,2][2,6,1,4,2][2,6,1,4,2], [2,6,4,2][2,6,4,2][2,6,4,2], [6,4,2][6,4,2][6,4,2], [6,4][6,4][6,4], [4][4][4] and [][][].
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 1;
int v[N] , n;
struct SegmentTree {
    vector<int>tree;
    SegmentTree(int _n) {
        tree.resize(4 * _n);
    }
    void build(int node , int nl , int nr) {
        if(nl == nr) {
            tree[node] = 1;
            return;
        }
        int mid = nl + (nr - nl) /2 ;
        build(2 * node + 1 , nl , mid);
        build(2 * node + 2, mid + 1 , nr);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    void upd(int node , int nl , int nr , int idx) {
        if(nl == nr && nl == idx) {
            tree[node] = 0;
            return;
        }
        if(nl > idx || nr < idx)return;
        int mid = nl + (nr - nl) / 2;
        upd(2 * node + 1 , nl , mid , idx);
        upd(2 * node + 2 , mid + 1 , nr , idx);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    int query(int node , int nl , int nr , int k) {
        if(nl == nr)return nl;
        int mid = nl + (nr - nl) /2 ;
        if(tree[2 * node + 1] >= k)return query(2 * node + 1 , nl , mid , k);
        else {
            k -= tree[2 * node + 1];
            return query(2 * node + 2 , mid + 1 , nr , k);
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i = 0;i < n;i++) {
        cin>>v[i];
    }
    SegmentTree seg(n);
    seg.build(0 , 0 , n - 1);
    for(int i = 0;i < n;i++) {
        int pos;cin>>pos;
        auto kth = seg.query(0 , 0 , n - 1 , pos);
        cout<<v[kth]<<" ";
        seg.upd(0 , 0 ,n - 1 , kth);
    }
}