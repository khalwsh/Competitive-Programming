/* problem statement text */
/*
CSES - Fixed-Length Paths I

Time limit: 1.00 s
Memory limit: 512 MB

Given a tree of nnn nodes, your task is to count the number of distinct paths that consist of exactly kkk edges.
Input
The first input line contains two integers nnn and kkk: the number of nodes and the path length. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print one integer: the number of paths.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 2
1 2
2 3
3 4
3 5

Output:
4
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
const int N = 2e5 + 10;
vector<int>adj[N];
int n , k , sz[N];
ll res = 0;
bool removed[N];
 
int cnt[N];
 
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
 
void dfs_add(int u , int p , int depth , int delta) {
    cnt[depth] += delta;
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_add(v , u , depth + 1 , delta);
    }
}
 
void dfs_ans(int u , int p , int depth) {
    if (depth <= k) res += cnt[k - depth];
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_ans(v , u , depth + 1);
    }
}
 
void decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
 
    // 1) count all paths passing through 'centroid'
    cnt[0] = 1;
    for (int v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_ans(v, centroid, 1);
        dfs_add(v, centroid, 1, +1);
    }
 
    // 2) roll back the counts
    for (int i = 0;i <= comp_sz;i++) cnt[i] = 0;
 
    // 3) remove the centroid and recurse in each resulting component
    removed[centroid] = true;
    for (int v : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}
 
 
int main() {
    PRE();
    cin >> n >> k;
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    decompose(0);
    cout<<res<<'\n';
}