const ll INF_LL = LLONG_MAX / 4;

/**
 * Finds the minimum total-weight (most negative) cycle-delta in the same graph.
 *
 * @param edges  vector of {u, v, w} edges (0-based)
 * @return       the smallest dp[N][v] - dp[k][v]; INF_LL if no cycle detected
 */
ll find_min_delta_negative_cycle(const vector<array<ll,3>>& edges) {
    // infer number of nodes
    int N = 0;
    for (auto &e : edges) {
        N = max<ll>(N, max(e[0], e[1]) + 1);
    }

    vector<vector<ll>> dp(N+1, vector<ll>(N, INF_LL));
    for (int v = 0; v < N; ++v)
        dp[0][v] = 0;

    for (int k = 1; k <= N; ++k) {
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            ll w = e[2];
            if (dp[k-1][u] < INF_LL) {
                dp[k][v] = min(dp[k][v], dp[k-1][u] + w);
            }
        }
    }

    ll min_delta = INF_LL;
    for (int v = 0; v < N; ++v) {
        if (dp[N][v] == INF_LL) continue;
        ll temp = -1e18;
        for (int k = 0; k < N; ++k) {
            if (dp[k][v] == INF_LL) continue;
            ll delta = dp[N][v] - dp[k][v];
            temp = max(temp, delta);
        }
        min_delta = min(min_delta , temp);
    }

    return min_delta;
}