int n;
int a[N] , sz[N] , bg[N] , freq[N] , ans[N] , x;
vector<int>adj[N];
int cnt = 0;
void dfs1(int node , int par) {
    sz[node] = 1;
    for(auto &val:adj[node]) {
        if(val == par)continue;
        dfs1(val , node);
        sz[node] += sz[val];
        if(bg[node] == -1 || sz[bg[node]] < sz[val])bg[node] = val;
    }
}
void collect(int node , int par , int value) {
    if(value == 1 && freq[a[node]] == 0)cnt++;
    if(value == -1 && freq[a[node]] == 1)cnt--;
    freq[a[node]] += value;
    for(auto &val:adj[node]) {
        if(val == par)continue;
        collect(val , node , value);
    }
}
void dfs2(int node , int par , bool keep = false) {
    for(auto &val:adj[node]) {
        if(val == par || val == bg[node])continue;
        dfs2(val , node , false);
    }
    if(bg[node] != -1)dfs2(bg[node] , node , true);

    // insert yourself
    if(!freq[a[node]])cnt++;
    freq[a[node]]++;
    // insert small sub trees
    for(auto &val:adj[node]) {
        if(val == par || val == bg[node])continue;
        collect(val , node , 1);
    }
    // calculate answer
    ans[node] = cnt;
    // delete you and the small children
    if(!keep) {
        collect(node , par , -1);
    }
}