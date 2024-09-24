// note when working on edges you should rebember it was [u , v] or [v , u] on the dfs so mark depth and set the edge value to the child (bigger in depth)
template<typename T>
struct SegmentTree {
    vector<T> tree, lazy;
    int n;
    void init(int _n) {
        this->n = _n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, -1e9);
    }
    static T Merge(T a, T b) {
        return max(a  ,  b);
    }
    void prop(int node, int nl, int nr) {
        if (lazy[node] != -1e9) {
            tree[node] = lazy[node];
            if (nl != nr) {
                lazy[2 * node + 1] = lazy[node];
                lazy[2 * node + 2] = lazy[node];
            }
            lazy[node] = -1e9;
        }
    }

    void modify(int node, int nl, int nr, int l, int r, T value) {
        prop(node, nl, nr);
        if (nl > r || nr < l) return;
        if (nl >= l && nr <= r) {
            lazy[node] = value;
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
        if (nl > r || nr < l) return T();
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
    vector<int>parent , heavy , depth , root , treePos;
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
            op(treePos[u] + Edge, treePos[v] );
    }

public:
    template <class G>
    void init(const G& graph , bool OnEdge = false) {
        Edge = OnEdge;
        int n = graph.size();
        parent.resize(n + 2);heavy.resize(n + 2 , -1);
        depth.resize(n + 2);root.resize(n + 2);
        treePos.resize(n + 2);
        parent[0] = -1;
        depth[0] = 0;
        dfs(graph, 0);
        for (int i = 0, currentPos = 0; i < n; ++i)
            if (parent[i] == -1 || heavy[parent[i]] != i)
                for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    treePos[j] = currentPos++;
                }
        seg.init(n);
    }

    void set(int v, const T& value) {
        seg.set(treePos[v], value);
    }

    void modifyPath(int u, int v, const T& value) {
        processPath(u, v, [this, &value](int l, int r) { seg.modify(l, r, value); });
    }

    T queryPath(int u, int v) {
        T res = T();
        processPath(u, v, [this, &res](int l, int r) { res = SegmentTree<T>::Merge(res , seg.query(l, r)); });
        return res;
    }
};