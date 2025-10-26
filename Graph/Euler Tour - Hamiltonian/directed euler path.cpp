const int N = 2e5 + 10;

int n, m;
vector<int> adj[N];
vector<int> tour;
int in[N], out[N];
int st = -1, en = -1;

bool euler() {
    for (int i = 0; i < n; i++) {
        if (abs(in[i] - out[i]) > 1)
            return false;

        if (in[i] == out[i] + 1) {
            if (en != -1) return false;
            en = i;
        }

        if (out[i] == in[i] + 1) {
            if (st != -1) return false;
            st = i;
        }
    }
    return true;
}

void dfs(int node) {
    while (out[node]) {
        dfs(adj[node][--out[node]]);
    }
    tour.emplace_back(node);
}

bool get() {
    if (!euler())
        return false;

    dfs(st);

    if ((int)tour.size() != m + 1)
        return false;

    reverse(tour.begin(), tour.end());
    return true;
}
