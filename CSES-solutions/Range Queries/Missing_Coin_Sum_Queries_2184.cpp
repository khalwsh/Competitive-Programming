/* problem statement text */
/*
CSES - Missing Coin Sum Queries

Time limit: 1.00 s
Memory limit: 512 MB

You have nnn coins with positive integer values. The coins are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Your task is to process qqq queries of the form: "if you can use coins a…ba \dots ba…b, what is the smallest sum you cannot produce?"
Input
The first input line has two integers nnn and qqq: the number of coins and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the value of each coin.
Finally, there are qqq lines that describe the queries. Each line has two values aaa and bbb: you can use coins a…ba \dots ba…b.
Output
Print the answer for each query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 3
2 9 1 2 7
2 4
4 4
1 5

Output:
4
1
6

Explanation: First you can use coins [9,1,2][9,1,2][9,1,2], then coins [2][2][2] and finally coins [2,9,1,2,7][2,9,1,2,7][2,9,1,2,7].
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
    ll sum;
    Node *l, *r;
    Node(ll s=0, Node* L=nullptr, Node* R=nullptr): sum(s), l(L), r(R) {}
};
 
vector<Node*> roots;
vector<ll> vals;
 
inline Node* getL(Node* p){ return p? p->l : nullptr; }
inline Node* getR(Node* p){ return p? p->r : nullptr; }
inline ll getS(Node* p)   { return p? p->sum : 0; }
 
Node* upd(int nl, int nr, int pos, ll delta, Node* ver){
    if(nl == nr){
        return new Node(getS(ver) + delta, nullptr, nullptr);
    }
    int mid = (nl + nr) >> 1;
    if(pos <= mid)
        return new Node(getS(ver) + delta, upd(nl, mid, pos, delta, getL(ver)), getR(ver));
    else
        return new Node(getS(ver) + delta, getL(ver), upd(mid+1, nr, pos, delta, getR(ver)));
}
 
ll sumQuery(int nl, int nr, Node* v1, Node* v2, int l, int r){
    if (v1 == nullptr) return 0;
    if(l > r || nl > r || nr < l) return 0;
    if(nl >= l && nr <= r) return getS(v1) - getS(v2);
    int mid = (nl + nr) >> 1;
    return sumQuery(nl, mid, getL(v1), getL(v2), l, r)
         + sumQuery(mid+1, nr, getR(v1), getR(v2), l, r);
}
 
int main(){
    PRE();
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    vals.reserve(n);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vals.push_back(a[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int S = (int)vals.size();
    roots.assign(n+1, nullptr);
    roots[0] = nullptr;
    for(int i=1;i<=n;i++){
        int pos = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
        roots[i] = upd(0, S-1, pos, a[i], roots[i-1]);
    }
 
    while(q--){
        int L, R; cin >> L >> R;
        ll cur = 1;
        while(true){
            int idx = int(upper_bound(vals.begin(), vals.end(), cur) - vals.begin()) - 1;
            ll x = 0;
            if(idx >= 0) x = sumQuery(0, S-1, roots[R], roots[L-1], 0, idx);
            if(x < cur){
                cout << cur << '\n';
                break;
            }
            cur = x + 1;
        }
    }
}