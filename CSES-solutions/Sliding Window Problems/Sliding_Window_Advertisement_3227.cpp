/* problem statement text */
/*
CSES - Sliding Window Advertisement

Time limit: 1.00 s
Memory limit: 512 MB

A fence consists of nnn vertical boards. The width of each board is 1 and their heights may vary.
You want to attach a rectangular advertisement to the fence. Your task is to calculate the maximum area of such an advertisement in each window of kkk vertical boards, from left to right.
Input
The first line contains two integers nnn and kkk: the width of the fence and the size of the window.
After this, there are nnn integers x1,x2,…,xnx_1, x_2, \dots, x_nx1​,x2​,…,xn​: the height of each board.
Output
Print n−k+1n - k + 1n−k+1 integers: the maximum areas of the advertisements.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
4 1 5 3 3 2 4 1

Output:
5 6 9 6 6 4
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
 
struct LineTree {
    struct TNode {
        ll k, b;
        TNode *l, *r;
 
        TNode() : k(0), b(0), l(nullptr), r(nullptr) {
        }
    };
 
    TNode *root;
    int dl;
    int dr;
 
    bool comp(ll ak, ll ab, ll bk, ll bb, ll x) { return ak * x + ab > bk * x + bb; }
 
    void _modify(TNode *&p, ll k, ll b, int l, int r, int ml, int mr) {
        if (p == nullptr) p = new TNode();
        int mid = (l + r) / 2;
        if (ml <= l && r <= mr) {
            if (l == r) {
                if (comp(k, b, p->k, p->b, l)) {
                    p->k = k;
                    p->b = b;
                }
                return;
            }
            if (comp(k, b, p->k, p->b, mid)) {
                std::swap(p->k, k);
                std::swap(p->b, b);
            }
            if (ml <= mid && comp(k, b, p->k, p->b, l)) _modify(p->l, k, b, l, mid, ml, mr);
            if (mid + 1 <= mr && comp(k, b, p->k, p->b, r)) _modify(p->r, k, b, mid + 1, r, ml, mr);
        } else {
            if (mid >= ml) _modify(p->l, k, b, l, mid, ml, mr);
            if (mid < mr) _modify(p->r, k, b, mid + 1, r, ml, mr);
        }
    }
 
    ll _query(TNode *&p, int pos, int l, int r) {
        if (p == nullptr) return 0;
        if (l == r) return p->k * pos + p->b;
        int mid = (l + r) / 2;
        ll ret = p->k * pos + p->b;
        if (pos <= mid) ret = std::max(ret, _query(p->l, pos, l, mid));
        else ret = std::max(ret, _query(p->r, pos, mid + 1, r));
        return ret;
    }
 
public:
    LineTree(int dl, int dr) : dl(dl), dr(dr), root(new TNode()) {
    }
 
    void modify(ll k, ll b, int l, int r) {
        // guard invalid ranges (keeps behavior safe)
        if (l > r) return;
        l = max(l, dl);
        r = min(r, dr);
        if (l > r) return;
        _modify(root, k, b, dl, dr, l, r);
    }
 
    ll query(int pos) { return _query(root, pos, dl, dr); }
};
 
int main() {
    PRE();
 
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
 
    map<ll, vector<int> > app;
    for (int i = 0; i < n; ++i) app[a[i]].push_back(i);
 
    set<int> o;
    for (int i = -1; i <= n; ++i) o.insert(i);
 
    LineTree lt(0, n);
 
    for (auto it = app.rbegin(); it != app.rend(); ++it) {
        ll v = it->first;
        auto &pos_list = it->second;
 
        for (int idx: pos_list) o.erase(idx);
 
        for (int idx: pos_list) {
            auto up = o.upper_bound(idx);
            int left_prev = *prev(up);
            int right_next = *up;
            int l = left_prev + 1;
            int r = right_next - 1;
 
            if (r - k + 1 >= 0) {
                lt.modify(v, (ll) (k - l) * v, max(0, l - k + 1), min(l, r - k + 1));
            }
            if (r - l + 1 >= k) {
                lt.modify(0, (ll) k * v, l, r - k + 1);
            }
            lt.modify(-v, (ll) (r + 1) * v, max(l, r - k + 1), r);
            if (r - k + 1 <= l) {
                lt.modify(0, (ll) (r - l + 1) * v, r - k + 1, l);
            }
        }
    }
 
    for (int i = 0; i + k - 1 < n; ++i) {
        cout << lt.query(i) << (i + k - 1 < n - 1 ? ' ' : '\n');
    }
    if (n - k + 1 <= 0) cout << "\n";
}