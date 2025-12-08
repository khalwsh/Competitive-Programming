/* problem statement text */
/*
CSES - Distinct Values Queries II

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the following types:

update the value at position kkk to uuu
check if every value in range [a,b][a, b][a,b] is distinct

Input
The first line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1, x_2,\dots, x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has three integers: either "111 kkk uuu" or "222 aaa bbb".
Output
For each query of type 2, print YES if every value in the range is distinct and NO otherwise.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi,u≤1091 \le x_i, u \le 10^91≤xi​,u≤109
1≤k≤n1 \le k \le n1≤k≤n
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 4
3 2 7 2 8
2 3 5
2 2 5
1 2 9
2 2 5

Output:
YES
NO
YES
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
const int N = 2e5 + 10;
int n , q , x[N];
array<int , 3> queries[N];
set<int> dq[N * 2];
 
struct Node {
    int mx_l , mn_r;
    Node(int a = -1e9 , int b = 1e9) {
        mx_l = a , mn_r = b;
    }
    Node operator+(const Node &a) {
        Node res;
        res.mx_l = max(mx_l , a.mx_l);
        res.mn_r = min(mn_r , a.mn_r);
        return res;
    }
};
 
struct SegmentTree {
    vector<Node>tree;
    SegmentTree(int _n) {
        tree.resize(4 * _n);
    }
    void upd(int node , int nl , int nr , int i , const Node &nw) {
        if (nl == nr) {
            tree[node] = nw;
            return;
        }
        int mid = nl + (nr - nl) / 2;
        if (i <= mid) upd(2 * node + 1 , nl , mid , i , nw);
        else upd(2 * node + 2 , mid + 1 ,nr , i , nw);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    Node query(int node , int nl , int nr , int l , int r) {
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return Node();
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1 , nl , mid , l , r) + query(2 * node + 2 ,mid + 1 , nr , l , r);
    }
}seg(N);
 
void insert(int idx , int val) {
    if (dq[val].empty()) {
        dq[val].insert(idx);
        seg.upd(0 , 0 , N - 1 , idx , Node());
        return;
    }
    auto nxt = dq[val].lower_bound(idx);
    if (nxt == dq[val].end()) {
        // you don't have next but you have previous
        auto prv = prev(nxt);
        seg.upd(0 , 0 , N - 1 , *prv , Node(seg.query(0 , 0 , N - 1 , *prv , *prv).mx_l , idx));
        seg.upd(0 , 0 , N - 1 , idx , Node(*prv , 1e9));
    }else if (nxt == dq[val].begin()) {
        // you have next but you don't have previous
        seg.upd(0 , 0 , N - 1 , idx , Node(-1e9 , *nxt));
        seg.upd(0 , 0 , N - 1 , *nxt , Node(idx , seg.query(0 , 0 , N - 1 , *nxt , *nxt).mn_r));
    }else {
        // you have next and previous
        auto prv = prev(nxt);
        seg.upd(0 , 0 , N - 1 , idx , Node(*prv , *nxt));
        seg.upd(0 , 0 , N - 1 , *prv , Node(seg.query(0 , 0 , N - 1 , *prv , *prv).mx_l , idx));
        seg.upd(0 , 0 , N - 1 , *nxt , Node(idx , seg.query(0 , 0 , N - 1 , *nxt , *nxt).mn_r));
    }
    dq[val].insert(idx);
}
 
void erase(int idx , int val) {
    auto it = dq[val].find(idx);
    assert(it != dq[val].end());
    auto nxt = next(it);
    if (it == dq[val].begin()) {
        // you have a next and no previous
        if (nxt == dq[val].end()) {
            dq[val].erase(it);
            return;
        }
        seg.upd(0 , 0 , N - 1 , *nxt , Node(-1e9 , seg.query(0 , 0 , N - 1 , *nxt , *nxt).mn_r));
        dq[val].erase(it);
        return;
    }
    if (nxt == dq[val].end()) {
        // you have a previous and no next
        auto prv = prev(it);
        seg.upd(0 , 0 , N - 1 , *prv , Node(seg.query(0 , 0 , N - 1 , *prv , *prv).mx_l , 1e9));
        dq[val].erase(it);
        return;
    }
    // now you have previous and next
    auto prv = prev(it);
    seg.upd(0 , 0 , N - 1 , *nxt , Node(*prv , seg.query(0 , 0 , N - 1 , *nxt , *nxt).mn_r));
    seg.upd(0 , 0 , N - 1 , *prv , Node(seg.query(0 , 0 , N - 1 , *prv , *prv).mx_l , *nxt));
    dq[val].erase(it);
}
 
int main() {
    PRE();
    cin >> n >> q;
    vector<int>all;
    for (int i = 1;i <= n;i++) cin >> x[i] , all.emplace_back(x[i]);
    for (int i = 0;i < q;i++) {
        for (int j = 0;j < 3;j++){
            cin >> queries[i][j];
            if (j == 2 && queries[i][0] == 1) all.emplace_back(queries[i][j]);
        }
    }
 
    sort(all.begin() , all.end());
    all.erase(unique(all.begin() , all.end()) , all.end());
 
    for (int i = 1;i <= n;i++) x[i] = lower_bound(all.begin() , all.end() , x[i]) - all.begin();
    for (int i = 0;i < q;i++) {
        if (queries[i][0] == 1) queries[i][2] = lower_bound(all.begin() , all.end() , queries[i][2]) - all.begin();
    }
    for (int i = 1;i <= n;i++) {
        insert(i , x[i]);
    }
    for (int i = 0;i < q;i++) {
        auto [type , l , r] = queries[i];
        if (type == 1) {
            // update
            erase(l , x[l]);
            x[l] = r;
            insert(l , x[l]);
        }else {
            // query
            auto v = seg.query(0 , 0 , N - 1 , l , r);
            if (v.mx_l >= l || v.mn_r <= r) cout << "NO";
            else cout << "YES";
            cout << '\n';
        }
    }
}