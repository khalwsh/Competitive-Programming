/* problem statement text */
/*
CSES - Bit Inversions

Time limit: 1.00 s
Memory limit: 512 MB

There is a bit string consisting of nnn bits. Then, there are some changes that invert one given bit. Your task is to report, after each change, the length of the longest substring whose each bit is the same.
Input
The first input line has a bit string consisting of nnn bits. The bits are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
The next line contains an integer mmm: the number of changes.
The last line contains mmm integers x1,x2,…,xmx_1,x_2,\ldots,x_mx1​,x2​,…,xm​ describing the changes.
Output
After each change, print the length of the longest substring whose each bit is the same.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤xi≤n1 \le x_i \le n1≤xi​≤n

Example
Input:
001011
3
3 2 5

Output:
4 2 3

Explanation: The bit string first becomes 000011, then 010011, and finally 010001.
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
 
struct Node {
    int lv, rv;
    int len1;
    int len2;
    int res;
    int size;
    Node() : lv(-1), rv(-1), len1(0), len2(0), res(0), size(0) {}
};
 
class SegmentTree {
public:
    int n;
    vector<Node> tree;
    vector<int> arr;
 
    SegmentTree(const vector<int>& a) {
        arr = a;
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }
 
    Node merge(const Node& left, const Node& right) {
        Node res;
        res.lv = left.lv;
        res.rv = right.rv;
        res.size = left.size + right.size;
        res.res = max(left.res, right.res);
        if (left.rv == right.lv) {
            res.res = max(res.res, left.len2 + right.len1);
        }
        res.len1 = left.len1;
        if (left.len1 == left.size && left.rv == right.lv) {
            res.len1 += right.len1;
        }
        res.len2 = right.len2;
        if (right.len2 == right.size && right.lv == left.rv) {
            res.len2 += left.len2;
        }
        return res;
    }
 
    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].lv = tree[v].rv = arr[tl];
            tree[v].len1 = tree[v].len2 = tree[v].res = 1;
            tree[v].size = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2 + 1, tl, tm);
            build(v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
 
    void update(int v, int tl, int tr, int pos , int val) {
        if (tl == tr) {
            arr[pos] = val;
 
            tree[v].lv = tree[v].rv = val;
            tree[v].len1 = tree[v].len2 = tree[v].res = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(v * 2 + 1, tl, tm, pos , val);
            } else {
                update(v * 2 + 2, tm + 1, tr, pos , val);
            }
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    Node query(int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr)
            return tree[v];
 
        int tm = (tl + tr) / 2;
 
        Node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        Node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
 
        if (left.res == 0)
            return right;
        if (right.res == 0)
            return left;
 
        return merge(left, right);
    }
    void update(int pos , int nval) {
        update(0, 0, n - 1, pos , nval);
    }
    int query(int l , int r) {
        return query(0 , 0 , n - 1 , l , r).res;
    }
};
 
int main() {
    PRE();
    string s;cin >> s;
    int n = s.size();
    vector<int> v(n);
    for (int i = 0; i < n;i++) v[i] = s[i] - '0';
    SegmentTree seg(v);
    int q;cin >> q;
    for (int i = 0;i < q;i++) {
        int u; cin >> u;
        u--;
        seg.update(u , 1 - v[u]);
        v[u] = 1 - v[u];
        cout << seg.query(0 , n - 1) << ' ';
    }
}