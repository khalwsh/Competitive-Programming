const ll INF_LL = LLONG_MAX / 4;

/**
 * Finds the minimum mean-weight cycle in a directed graph.
 *
 * @param edges  vector of {u, v, w} edges (0-based)
 * @return       the minimum cycle mean as a long double (>= 0 if no negative-mean cycle)
 */
long double find_min_mean_cycle(const vector<array<ll,3>>& edges) {
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

    long double mu = numeric_limits<long double>::infinity();
    for (int v = 0; v < N; ++v) {
        if (dp[N][v] == INF_LL) continue;
        long double local_max = -numeric_limits<long double>::infinity();
        for (int k = 0; k < N; ++k) {
            if (dp[k][v] == INF_LL) continue;
            long double mean = (long double)(dp[N][v] - dp[k][v]) / (long double)(N - k);
            local_max = max(local_max, mean);
        }
        mu = min(mu, local_max);
    }

    return mu;
}