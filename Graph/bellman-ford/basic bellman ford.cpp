struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;

void solve(int source)
{
    vector<int> d(n, inf);
    d[source] = 0;
    for (int i = 0; i < n - 1; ++i)
        for (Edge e : edges)
            if (d[e.a] < inf)
                d[e.b] = min(d[e.b], d[e.a] + e.cost);
    // display d, for example, on the screen
}