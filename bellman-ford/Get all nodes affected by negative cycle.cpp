struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;

vector<int> solve(int source)
{
    vector<int> d(n, inf);
    d[source] = 0;
    for (int i = 0; i < n - 1; ++i)
        for (Edge e : edges)
            if (d[e.a] < inf)
                d[e.b] = min(d[e.b], d[e.a] + e.cost);

    vector<int>ref = d;
    for (int i = 0; i < n; ++i)
        for (Edge e : edges)
            if (d[e.a] < inf)
                d[e.b] = min(d[e.b], d[e.a] + e.cost);

    vector<int>nodes;
    
    for(int i=0;i<n;i++){
        if(ref[i] != d[i]){
	   nodes.emplace_back(i);
        }
    }
    return nodes;
}