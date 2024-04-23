struct Edge {
    int a, b, cost;
};
int n, m;
vector<Edge> edges;
vector<int> solve(int source,int goal) {
    vector<int> d(n, inf);
    d[source] = 0;
    vector<int> p(n, -1);

    for (int i=0;i<n-1;i++) {
        bool any = false;
        for (Edge e : edges)
            if (d[e.a] < inf)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = d[e.a] + e.cost;
                    p[e.b] = e.a;
                    any = true;
                }
        if (!any)
            break;
    }

    if (d[goal] == inf)
            return vector<int>{-1};
    else {
            vector<int> path;
            for (int cur = goal; cur != -1; cur = p[cur])
            path.push_back(cur);
            reverse(path.begin(), path.end());
            return path;
         }
}