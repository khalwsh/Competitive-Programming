const ll inf = 1e18;
pair<ll, vector<pair<int, int>>>
hungarianAlgorithm(const vector<vector<ll>>& cost) {
    int n = cost.size();
    vector<ll> u(n + 1, 0), v(n + 1, 0);
    vector<int> p(n + 1, 0), way(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        vector<ll> minv(n + 1, inf);
        vector<bool> used(n + 1, false);
        int j0 = 0;
        p[0] = i;

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = inf;

            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    ll cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<pair<int, int>> assignment;
    for (int j = 1; j <= n; j++)
        if (p[j])
            assignment.emplace_back(p[j], j);

    return {-v[0], assignment};
}