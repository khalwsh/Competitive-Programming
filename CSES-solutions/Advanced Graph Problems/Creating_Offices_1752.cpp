/* problem statement text */
/*
CSES - Creating Offices

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and n−1n-1n−1 roads between them. There is a unique route between any two cities, and their distance is the number of roads on that route.
A company wants to have offices in some cities, but the distance between any two offices has to be at least ddd. What is the maximum number of offices they can have?
Input
The first input line has two integers nnn and ddd: the number of cities and the minimum distance. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are n−1n-1n−1 lines describing the roads. Each line has two integers aaa and bbb: there is a road between cities aaa and bbb.
Output
First print an integer kkk: the maximum number of offices. After that, print the cities which will have offices. You can print any valid solution.
Constraints

1≤n,d≤2⋅1051 \le n,d \le 2 \cdot 10^51≤n,d≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 3
1 2
2 3
3 4
3 5

Output:
2
1 4
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
 
/*
- remember to init centroid parent with -1
- this will return centroid_tree which is tree of height log(n)
- you will build lca on original tree , consider making it with Euler tour because already height is log(n)
- usually you need to update the path from node u to root and when query take the best from u to root adding the cost of moving
*/
// remember to pass LCA to the dsu , build LCA before passing it
template <class T>
struct sparsetable {
    int n, LOG;
    vector<vector<T>> st;
 
    sparsetable() {}
 
    sparsetable(vector<T> a) {
        n = a.size();
        LOG = bit_width(a.size()) + 1;
        st = vector<vector<T>>(LOG, vector<T>(n));
        st[0] = a;
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
 
    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
 
struct LCA {
    int timer;
    vector<vector<int>> g;
    vector<int> tin, tout, dep;
    vector<pair<int, int>> flat;
    sparsetable<pair<int, int>> st;
 
    LCA() {}
    LCA(int n) : timer(0), g(n), tin(n), tout(n), dep(n), flat(2 * n) {}
 
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    void dfs(int v, int p) {
        flat[timer] = {dep[v], v};
        tin[v] = timer++;
        for (int u : g[v]) {
            if (u == p) continue;
            dep[u] = dep[v] + 1;
            dfs(u, v);
            flat[timer++] = {dep[v], v};
        }
        tout[v] = timer;
    }
 
    void build(int root) {
        dfs(root, -1);
        st = sparsetable(flat);
    }
 
    int get_lca(int u, int v) {
        auto [l, r] = minmax(tin[u], tin[v]);
        return st.query(l, r).second;
    }
 
    int get_dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
    }
};
 
LCA lca;
 
const int N = 2e5 + 10 , K = 19;
int depth[N];
vector<int>adj[N] , centroid_tree[N];
int centroid_parent[N];
int n , m , sz[N] , centroid_tree_root = -1;
vector<int> by_dep[N];
bool removed[N];
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p || removed[v])continue;
        sz[u] += dfs_sz(v , u);
    }
    return sz[u];
}
 
int dfs_centroid(int u, int p, int s) {
    for (auto &v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > s) return dfs_centroid(v , u , s);
    }
    return u;
}
 
int decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
    if (centroid_tree_root == -1) centroid_tree_root = centroid;
    removed[centroid] = true;
    for (auto &v : adj[centroid]) {
        if (!removed[v]) {
            int x = decompose(v);
            centroid_tree[centroid].emplace_back(x);
            centroid_tree[x].emplace_back(centroid);
            centroid_parent[x] = centroid;
        }
    }
    return centroid;
}
int dist[N];
void upd(int u) {
    dist[u] = 0;
    int temp = u;
    while (centroid_parent[u] != -1) {
        u = centroid_parent[u];
        dist[u] = min(dist[u] , lca.get_dist(u , temp));
    }
}
int get(int u) {
    int res = dist[u];
    int temp = u;
    while (centroid_parent[u] != -1) {
        u = centroid_parent[u];
        res = min(res , dist[u] + lca.get_dist(u , temp));
    }
    return res;
}
void dfs2(int u , int p , int cur = 1) {
    by_dep[cur].emplace_back(u);
    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs2(v , u , cur + 1);
    }
}
int main() {
    PRE();
    cin >> n;
    int D;cin >> D;
    lca = LCA(n);
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin >> u >> v;
        adj[u - 1].emplace_back(v - 1);
        adj[v - 1].emplace_back(u - 1);
        lca.add_edge(u - 1 , v - 1);
    }
    lca.build(0);
    memset(dist , '?' , sizeof dist);
    memset(centroid_parent , -1 , sizeof centroid_parent);
    decompose(0);
    int res = 0;
    vector<int> nodes;
    dfs2(0 , -1 , 1);
    for (int i = N - 1;i >= 1;i--) {
        for (auto &v : by_dep[i]) {
            if (get(v) >= D) {
                res++ , upd(v) , nodes.emplace_back(v);
            }
        }
    }
    cout << res << '\n';
    sort(nodes.begin() , nodes.end());
    for (auto &val : nodes) cout << ++val << " ";
}