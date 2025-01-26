struct LCA {
private:
    vector<vector<int>> adj;
    vector<int> depth, first_occurrence;
    vector<pair<int, int>> euler_tour;
    vector<vector<pair<int, int>>> sparse_table;
    int n, timer = 0;

    static int log2_floor(int x) {
        return 31 - __builtin_clz(x);
    }

    void dfs(int node, int parent, int d) {
        depth[node] = d;
        first_occurrence[node] = (int)euler_tour.size();
        euler_tour.emplace_back(d, node);

        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                dfs(neighbor, node, d + 1);
                euler_tour.emplace_back(d, node);
            }
        }
    }

    void build_sparse_table() {
        int m = (int)euler_tour.size();
        int log_m = log2_floor(m) + 1;

        sparse_table.assign(log_m, vector<pair<int, int>>(m));
        sparse_table[0] = euler_tour;

        for (int j = 1; (1 << j) <= m; ++j) {
            for (int i = 0; i + (1 << j) <= m; ++i) {
                sparse_table[j][i] = min(sparse_table[j - 1][i], sparse_table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    pair<int, int> range_min_query(int l, int r) {
        int len = r - l + 1;
        int log_len = log2_floor(len);
        return min(sparse_table[log_len][l], sparse_table[log_len][r - (1 << log_len) + 1]);
    }

public:
    LCA(int n, const vector<vector<int>>& adj) : n(n), adj(adj) {
        depth.assign(n, 0);
        first_occurrence.assign(n, -1);
        euler_tour.clear();

        dfs(0, -1, 0);
        build_sparse_table();
    }

    int get(int u, int v) {
        int left = first_occurrence[u];
        int right = first_occurrence[v];
        if (left > right) swap(left, right);
        return range_min_query(left, right).second;
    }
};