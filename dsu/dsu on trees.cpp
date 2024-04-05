int arr[N],siz[N],res[N];
vector<int>adj[N];
vector<int>v[N];
map<int,int>s;
void S(int node,int par){
    siz[node] = 1;
    for(auto &val:adj[node]){
        if(val == par)continue;
        S(val,node);
        siz[node]+=siz[val];
    }
}
void dfs(int node,int par,bool keep) {
    int Max = -1, BigChild = -1;
    //find the biggest child
    for (auto &val: adj[node]) {
        if (Max <= siz[val] && val != par) {
            Max = siz[val];
            BigChild = val;
        }
    }
    //make dfs calls for light children and mark them that you should erase your answer to not ruin the global answer
    for (auto &val: adj[node]) {
        if (val != BigChild && val != par) {
            dfs(val, node, false);
        }
    }
    //if it's not a leaf node do dfs for big child and don't erase it's content
    if (~BigChild) {
        dfs(BigChild, node, true);
        swap(v[node], v[BigChild]);//O(1) operation that make cur node have the big child content to append
    }
    //adding my self as part of my sub tree and adding my self to the answer
    v[node].emplace_back(node);
    s[arr[node]]++;
    //iterate on small children subtrees and update the answer
    for (auto &val: adj[node]) {
        if (val != par && val != BigChild) {
            for(auto &x:v[val]) {
                v[node].emplace_back(x);
                s[arr[x]]++;
            }
        }
    }
    //calculating the answer for node
    res[node] = (int) s.size();
    //if you are light child erase your effect on the shared array that help me to answer to the nodes
    if (!keep) {
        for (auto &val: v[node]) {
            s[arr[val]]--;
            if (s[arr[val]] == 0)s.erase(arr[val]);
        }
    }
}