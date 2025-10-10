// -----------------------
// Defenition : there is an edge from u to v if every path from source to v pass through u
// idom[i] = immediate dominator of node with DFS index i (i.e., dominator-tree parent in DFS-index space).
// domTree[u] adjacency list of u in the dominator tree.

// Usage example of Dominator Tree:
// init(n);
// add directed edges to g[u] with u in [1..n];
// build(root);
// now domTree[u] holds neighbors of u in the dominator tree (for reachable nodes).
// -----------------------
const int N = 200000 + 5;
vector<int> g[N];
vector<int> rg[N], bucket[N];
vector<int> domTree[N];
int sdom[N], par[N], idom[N], dsu[N], label[N];
int id[N], rev_[N], T;

void init(int n) {
    T = 0;
    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        rg[i].clear();
        bucket[i].clear();
        domTree[i].clear();
        id[i] = 0;
        rev_[i] = 0;
        sdom[i] = par[i] = idom[i] = dsu[i] = label[i] = 0;
    }
}

int find_(int u, int x = 0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find_(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}

void dfs(int u) {
    id[u] = ++T;
    rev_[T] = u;
    label[T] = sdom[T] = dsu[T] = T;
    for (int v: g[u]) {
        if (!id[v]) {
            dfs(v);
            par[id[v]] = id[u];
        }
        if (id[v]) rg[id[v]].push_back(id[u]);
    }
}

void build(int root) {
    dfs(root);
    int n = T;

    for (int i = n; i >= 1; --i) {
        for (int v: rg[i]) {
            int u = find_(v);
            sdom[i] = min(sdom[i], sdom[u]);
        }
        if (i > 1) bucket[sdom[i]].push_back(i);

        for (int w: bucket[i]) {
            int v = find_(w);
            if (sdom[v] == sdom[w]) idom[w] = sdom[w];
            else idom[w] = v;
        }

        if (i > 1) dsu[i] = par[i];
    }

    for (int i = 2; i <= n; ++i) {
        if (idom[i] != sdom[i]) idom[i] = idom[idom[i]];
        int u = rev_[idom[i]];
        int v = rev_[i];
        domTree[u].push_back(v);
        domTree[v].push_back(u);
    }
}