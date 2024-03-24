const int Log = 21;
int up[N][Log],depth[N],parent[N],root = 0;
vector<int>adj[N];
void rooting(){
    queue<pair<int,int>>q;
    q.push({root,-1});
    parent[root] = root;
    while(!q.empty()){
        int node = q.front().first;
        int par = q.front().second;
        q.pop();
        for(auto &val:adj[node]){
            if(val==par)continue;
            parent[val] = node;
            q.push({val,node});
        }
    }
}
void MarkDepth(int node,int par,int Dist = 0) {
    depth[node] = Dist;
    for (auto &val: adj[node]) {
        if (val == par)continue;
        MarkDepth(val, node,  Dist+ 1);
    }
}
void build(int n) {
    MarkDepth(root, -1);
    for (auto &val: up)for (auto &i: val)i = -1;
    parent[root] = root;// to handle non-existing edges
    for (int i = 0; i < n; i++)up[i][0] = parent[i];
    for (int i = 1; i < Log; i++) {
        for (int j = 0; j < n; j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
}
int walk(int node,int k) {
    if (depth[node] < k)return -1;
    for (int i = 0; i < Log; i++) {
        if (k & (1 << i))node = up[node][i];
    }
    return node;
}
int LCA(int a,int b){
    if(depth[a]<depth[b])swap(a,b);
    a = walk(a,depth[a] - depth[b]);
    if(a==b)return a;
    for(int i = Log - 1;i>=0;i--){
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    assert(parent[a]==parent[b]);
    return parent[a];
}
int dist(int a,int b){
    return depth[a] + depth[b] - 2 * depth[LCA(a,b)];
}
void init(){
    for(int i=0;i<n;i++)adj[i].clear();
}