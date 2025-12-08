/* problem statement text */
/*
CSES - MST Edge Set Check

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected weighted graph and edge sets, determine for each set if the edges can be included in a minimum spanning tree.
Input
The first line has three integers nnn,  mmm and qqq: the number of nodes, edges and edge sets. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The following mmm lines describe the edges. Each line has three integers aaa, bbb, www: there is an edge between nodes aaa and bbb with weight www. The edges are numbered 1,2,…,m1,2,\dots,m1,2,…,m in the input order.
The following 2q2q2q lines describe the edge sets. For each set, the first line contains its size and the second line contains its edges. The total number of edges in all sets is at most mmm.
You can assume that the graph is connected and simple and each edge appears at most once in the graph.
Output
For each edge set, print YES if the edges can be included in the minimum spanning tree and NO otherwise.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m,q≤2⋅1051 \le m, q \le 2 \cdot 10^51≤m,q≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤w≤1091 \le w \le 10^91≤w≤109

Example
Input:
5 6 4
1 2 4
1 3 2
2 4 2
3 4 1
3 5 3
4 5 3
3
2 3 4
1
1
2
2 6
2
5 6

Output:
YES
NO
YES
NO
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
struct E { int u, v; ll w; };
 
struct D {
    vector<int> p;
    D() {}
    D(int n) { init(n); }
    void init(int n) { p.assign(n+1, -1); }
    int f(int x) { return p[x] < 0 ? x : p[x] = f(p[x]); }
    bool u(int a, int b) {
        a = f(a); b = f(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a,b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
 
    vector<E> e(m+1);
    vector<ll> ws;
    ws.reserve(m);
 
    unordered_map<ll, vector<int>> ew;
    ew.reserve(m * 2);
 
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        ew[e[i].w].push_back(i);
        ws.push_back(e[i].w);
    }
 
    vector<bool> ans(q, true);
    unordered_map<ll, vector<pair<int,int>>> qw;
    qw.reserve(m * 2);
 
    for (int i = 0; i < q; ++i) {
        int k; cin >> k;
        while (k--) {
            int id; cin >> id;
            qw[e[id].w].push_back({i, id});
        }
    }
 
    sort(ws.begin(), ws.end());
    ws.erase(unique(ws.begin(), ws.end()), ws.end());
 
    D g(n);
 
    for (ll w : ws) {
        auto it = qw.find(w);
        if (it != qw.end()) {
            unordered_map<int, vector<int>> grp;
            grp.reserve(it->second.size() * 2);
 
            for (auto &x : it->second)
                grp[x.first].push_back(x.second);
 
            for (auto &gg : grp) {
                int qi = gg.first;
                if (!ans[qi]) continue;
 
                auto &lst = gg.second;
                vector<int> nd;
                nd.reserve(lst.size() * 2);
                bool cyc = false;
 
                for (int id : lst) {
                    int a = g.f(e[id].u);
                    int b = g.f(e[id].v);
                    if (a == b) { cyc = true; break; }
                    nd.push_back(a);
                    nd.push_back(b);
                }
 
                if (cyc) { ans[qi] = false; continue; }
 
                sort(nd.begin(), nd.end());
                nd.erase(unique(nd.begin(), nd.end()), nd.end());
 
                unordered_map<int,int> mp;
                mp.reserve(nd.size() * 2);
                for (int i = 0; i < (int)nd.size(); ++i)
                    mp[nd[i]] = i;
 
                vector<int> tp(nd.size(), -1);
 
                function<int(int)> tf = [&](int x) {
                    int r = x;
                    while (tp[r] >= 0) r = tp[r];
                    int c = x;
                    while (c != r) {
                        int nxt = tp[c];
                        tp[c] = r;
                        c = nxt;
                    }
                    return r;
                };
 
                auto tu = [&](int a, int b) {
                    a = tf(a); b = tf(b);
                    if (a == b) return false;
                    if (tp[a] > tp[b]) swap(a,b);
                    tp[a] += tp[b];
                    tp[b] = a;
                    return true;
                };
 
                bool bad = false;
                for (int id : lst) {
                    int a = mp[g.f(e[id].u)];
                    int b = mp[g.f(e[id].v)];
                    if (!tu(a, b)) { bad = true; break; }
                }
 
                if (bad) ans[qi] = false;
            }
        }
 
        auto it2 = ew.find(w);
        if (it2 != ew.end()) {
            for (int id : it2->second)
                g.u(e[id].u, e[id].v);
        }
    }
 
    for (int i = 0; i < q; ++i)
        cout << (ans[i] ? "YES" : "NO") << '\n';
}