// note you need to apply changes to segment tree logic
template<typename T>
struct SegmentTree {
    vector<T> tree, lazy;
    int n;

    void init(int _n) {
        this->n = _n;
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    static T Merge(T a, T b) {
        return a + b;
    }

    void prop(int node, int nl, int nr) {
        // play here
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (nl != nr) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void modify(int node, int nl, int nr, int l, int r, T value) {
        prop(node, nl, nr);
        if (nl > r || nr < l) return;
        if (nl >= l && nr <= r) {
            // play here
            lazy[node] += value;
            prop(node, nl, nr);
            return;
        }
        int mid = nl + (nr - nl) / 2;
        modify(2 * node + 1, nl, mid, l, r, value);
        modify(2 * node + 2, mid + 1, nr, l, r, value);
        tree[node] = Merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    T query(int node, int nl, int nr, int l, int r) {
        prop(node, nl, nr);
        if (nl > r || nr < l) return -1e15; // Neutral value for max operation
        if (nl >= l && nr <= r) return tree[node];
        int mid = nl + (nr - nl) / 2;
        return Merge(query(2 * node + 1, nl, mid, l, r), query(2 * node + 2, mid + 1, nr, l, r));
    }

    void set(int idx, T value) {
        modify(0, 0, n - 1, idx, idx, value);
    }

    void modify(int l, int r, T value) {
        modify(0, 0, n - 1, l, r, value);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

template <class T>
class HeavyLight {
    SegmentTree<T> seg;
    bool Edge = false;
    vector<int> parent, heavy, depth, root, treePos;
    vector<int> siz;
    int cur_pos = 0;

    template <class G>
    int dfs(const G& graph, int v) {
        int size = 1, maxSubtree = 0;
        for (int u : graph[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            int subtree = dfs(graph, u);
            if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
            size += subtree;
        }
        siz[v] = size;
        return size;
    }

    template <class BinaryOperation>
    void processPath(int u, int v, BinaryOperation op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(treePos[root[v]], treePos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        if(treePos[u] == treePos[v] && !Edge || treePos[u] != treePos[v])
            op(treePos[u] + Edge, treePos[v]);
    }

    template <class G>
    void decompose(int v, int h, const G& adj) {
        root[v] = h;
        treePos[v] = cur_pos++;
        if (heavy[v] != -1) {
            decompose(heavy[v], h, adj);
        }
        for (int u : adj[v]) {
            if (u != parent[v] && u != heavy[v]) {
                decompose(u, u, adj);
            }
        }
    }
public:
    template <class G>
    void init(const G& graph, bool OnEdge = false) {
        Edge = OnEdge;
        int n = graph.size();
        parent.resize(n);
        heavy.resize(n, -1);
        depth.resize(n);
        root.resize(n);
        treePos.resize(n);
        siz.resize(n);
        parent[0] = -1;
        depth[0] = 0;
        dfs(graph, 0);
        decompose(0, 0, graph);
        seg.init(n);
    }

    void set(int v, const T& value) {
        seg.set(treePos[v], value);
    }

    void modifyPath(int u, int v, const T& value) {
        processPath(u, v, [this, &value](int l, int r) { seg.modify(l, r, value); });
    }

    void modifySubtree(int v, T value) {
        seg.modify(treePos[v], treePos[v] + siz[v] - 1, value);
    }

    T queryPath(int u, int v) {
        T res = T();
        processPath(u, v, [this, &res](int l, int r) { res = SegmentTree<T>::Merge(res, seg.query(l, r)); });
        return res;
    }
};