vector<pair<int,int>> adj[N];
int n , m, k;
signed main() {
    khaled
    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i){
        int u , v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v , w);
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    vector<int> cnt(n) , ans;
    int start = 0 , end = n - 1;
    q.push({0 , start});
    while(q.size() && cnt[end] < k){
        auto [d , u] = q.top(); q.pop();
        cnt[u]++;
        if(u == end) ans.emplace_back(d);
        if(cnt[u] <= k){
            for(auto &[v,  w] : adj[u]) {
                if (cnt[v] < k)
                    q.push({(w + d), v});
            }
        }
    }
    sort(ans.begin() , ans.end());
    for(auto &w : ans) cout << w << " ";
}
