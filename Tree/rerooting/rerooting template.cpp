namespace reroot {
    const auto exclusive = [](const auto& a, const auto& base, const auto& merge_into, int vertex) {
        int n = (int)a.size();
        using Aggregate = std::decay_t<decltype(base)>;
        std::vector<Aggregate> b(n, base);
        for (int bit = (int)std::__lg(n); bit >= 0; --bit) {
            for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
            int sz = n - (n & !bit);
            for (int i = 0; i < sz; ++i) {
                int index = (i >> bit) ^ 1;
                b[index] = merge_into(b[index], a[i], vertex, i);
            }
        }
        return b;
    };
    // MergeInto : Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
    // Base : Vertex(int) -> Aggregate
    // FinalizeMerge : Aggregate * Vertex(int) * EdgeIndex(int) -> Value
    const auto rerooter = [](const auto& g, const auto& base, const auto& merge_into, const auto& finalize_merge) {
        int n = (int)g.size();
        using Aggregate = std::decay_t<decltype(base(0))>;
        using Value = std::decay_t<decltype(finalize_merge(base(0), 0, 0))>;
        std::vector<Value> root_dp(n), dp(n);
        std::vector<std::vector<Value>> edge_dp(n), redge_dp(n);

        std::vector<int> bfs, parent(n);
        bfs.reserve(n);
        bfs.push_back(0);
        for (int i = 0; i < n; ++i) {
            int u = bfs[i];
            for (auto v : g[u]) {
                if (parent[u] == v) continue;
                parent[v] = u;
                bfs.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            int u = bfs[i];
            int p_edge_index = -1;
            Aggregate aggregate = base(u);
            for (int edge_index = 0; edge_index < (int)g[u].size(); ++edge_index) {
                int v = g[u][edge_index];
                if (parent[u] == v) {
                    p_edge_index = edge_index;
                    continue;
                }
                aggregate = merge_into(aggregate, dp[v], u, edge_index);
            }
            dp[u] = finalize_merge(aggregate, u, p_edge_index);
        }

        for (auto u : bfs) {
            dp[parent[u]] = dp[u];
            edge_dp[u].reserve(g[u].size());
            for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
            auto dp_exclusive = exclusive(edge_dp[u], base(u), merge_into, u);
            redge_dp[u].reserve(g[u].size());
            for (int i = 0; i < (int)dp_exclusive.size(); ++i) redge_dp[u].push_back(finalize_merge(dp_exclusive[i], u, i));
            root_dp[u] = finalize_merge(n > 1 ? merge_into(dp_exclusive[0], edge_dp[u][0], u, 0) : base(u), u, -1);
            for (int i = 0; i < (int)g[u].size(); ++i) {
                dp[g[u][i]] = redge_dp[u][i];
            }
        }

        return std::make_tuple(std::move(root_dp), std::move(edge_dp), std::move(redge_dp));
    };
}
// to solve re rooting problem you fill those three function then call re rooter sending them and the graph

using Aggregate = ll;
using Value = ll;
auto base = [](int vertex) -> Aggregate {
    // your dp initialization
    return 0;
};
auto merge_into = [](Aggregate vertex_dp, Value neighbor_dp, int vertex, int edge_index) -> Aggregate {
    // how to merge answer of the vertex and it's child
   // note edge index is the index in the adj list like adj[3] : 2 1 12 , then the edge_index of 2 represent the edge 3 --> 12
    return 0;
};
auto finalize_merge = [&](Aggregate vertex_dp, int vertex, int edge_index) -> Value {
    // before finish the dfs any work with the dp value
    return 0;
};