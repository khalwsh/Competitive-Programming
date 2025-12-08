/* problem statement text */
/*
CSES - Tree Isomorphism II

Time limit: 1.00 s
Memory limit: 512 MB

Given two (not rooted) trees, your task is to find out if they are isomorphic, i.e., it is possible to draw them so that they look the same.
Input
The first input line has an integer ttt: the number of tests. Then, there are ttt tests described as follows:
The first line has an integer nnn: the number of nodes in both trees. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are n−1n-1n−1 lines describing the edges of the first tree, and finally n−1n-1n−1 lines describing the edges of the second tree.
Output
For each test, print "YES", if the trees are isomorphic, and "NO" otherwise.
Constraints

1≤t≤10001 \le t \le 10001≤t≤1000
2≤n≤1052 \le n \le 10^52≤n≤105
the sum of all values of nnn is at most 10510^5105

Example
Input:
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2

Output:
YES
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
static inline ll split(ll x) {
    x += 0x9e3779b974a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1e4e5b9LL;
    x = (x ^ (x >> 27)) * 0x94d049bb33111ebLL;
    return x ^ (x >> 31);
}
 
ll combine(const vector<ll>& child) {
    ll h = 146959810393466537LL;
    for (ll x : child) {
        ll k = x + 0x9e3779b97f4a7c15ULL;
        h ^= k + (h << 6) + (h >> 2);
        h *= 1099511628211ULL;
    }
    h ^= (0xff51afd7ed558cLL ^ (ll)child.size());
    return split(h);
}
 
vector<int> find_centers(int n, const vector<vector<int>>& adj) {
    if (n == 1) return {1};
    vector<int> deg(n+1);
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        deg[i] = (int)adj[i].size();
        if (deg[i] <= 1) q.push(i);
    }
    int removed = 0;
    while (!q.empty()) {
        if (n - removed <= 2) {
            vector<int> centers;
            while (!q.empty()) { centers.push_back(q.front()); q.pop(); }
            return centers;
        }
        int sz = q.size();
        removed += sz;
        for (int i = 0; i < sz; ++i) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (--deg[v] == 1) q.push(v);
            }
        }
    }
    return {};
}
 
ll rooted_hash(int root, const vector<vector<int>>& adj) {
    int n = (int)adj.size() - 1;
    vector<int> parent(n+1, -1), order; order.reserve(n);
    stack<int> st;
    st.push(root); parent[root] = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        order.push_back(u);
        for (int v : adj[u]) if (parent[v] == -1) {
            parent[v] = u;
            st.push(v);
        }
    }
    vector<ll> h(n+1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        vector<ll> ch; ch.reserve(adj[u].size());
        for (int v : adj[u]) if (v != parent[u]) ch.push_back(h[v]);
        sort(ch.begin(), ch.end());
        h[u] = combine(ch);
    }
    return h[root];
}
 
ll tree_hash(const vector<vector<int>>& adj) {
    int n = (int)adj.size() - 1;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    vector<int> centers = find_centers(n, adj);
    if (centers.size() == 1) return rooted_hash(centers[0], adj);
    ll h1 = rooted_hash(centers[0], adj);
    ll h2 = rooted_hash(centers[1], adj);
    if (h1 > h2) swap(h1, h2);
    vector<ll> pairv = {h1, h2};
    return combine(pairv);
}
int main() {
    PRE();
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> a(n+1), b(n+1);
        for (int i = 0; i < n-1; ++i) {
            int u,v; cin >> u >> v;
            a[u].push_back(v); a[v].push_back(u);
        }
        for (int i = 0; i < n-1; ++i) {
            int u,v; cin >> u >> v;
            b[u].push_back(v); b[v].push_back(u);
        }
 
        ll ha = tree_hash(a);
        ll hb = tree_hash(b);
        cout << (ha == hb ? "YES" : "NO") << '\n';
    }
}