int n , m;
const int N = 501;
int cap[N][N] , was[N][N];
pair<int , vector<int>>Get(int source , int sink) {
    vector<int>parent(n , -1) , vis(n , 0) , dist(n , 0);
    queue<int>q;
    q.push(source);
    vis[source] = true;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int i = 0;i < n;i++) {
            if(!vis[i] && cap[node][i]) {
                q.push(i);
                vis[i] = true;
                parent[i] = node;
            }
        }
    }
    if(!vis[sink])return {0 , {}};
    vector<int>path;
    while(sink != -1)path.emplace_back(sink) , sink = parent[sink];
    reverse(path.begin() , path.end());
    return {1 , path};
}
pair<int , vector<pair<int , int>>> Flow(int source , int sink) {
    int flow = 0;
    while(true) {
        auto [new_flow , path] = Get(source , sink);
        // cout<<new_flow<<endl;
        if(!new_flow)break;
        for(int i = 1;i < path.size();i++) {
            cap[path[i - 1]][path[i]] -= new_flow;
            cap[path[i]][path[i - 1]] += new_flow;
        }
        flow += new_flow;
    }
    vector<pair<int , int>>edges;
    vector<int> vis(n, 0);
    queue<int> q;
    q.push(source);
    vis[source] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if (!vis[i] && cap[node][i] > 0) {
                q.push(i);
                vis[i] = true;
            }
        }
    }

    // Identify min-cut edges
    for (int i = 0; i < n; i++) {
        if (vis[i]) { // Node i is in set S
            for (int j = 0; j < n; j++) {
                if (!vis[j] && was[i][j] > 0) { // Node j is in set T
                    edges.emplace_back(i, j);
                }
            }
        }
    }

    return {flow, edges};
}