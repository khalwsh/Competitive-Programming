const int N = 1e6+9 , LOG = 20;
int in[N] , out[N] , dep[N] , up[N][LOG], timer;
vector<int> adj[N] , virtual_tree[N];

void pre_dfs(int u , int p){
    in[u] = ++timer;

    dep[u] = dep[p] + 1;
    up[u][0] = p;
    for(int x = 1; x < LOG; ++x){
        up[u][x] = up[ up[u][x-1] ][x-1];
    }

    for(auto &v : adj[u]) if(v != p){
        pre_dfs(v,u);
    }

    out[u] = timer;
}

int lca(int u , int v){
    if(dep[u] < dep[v]) swap(u,v);
    int k = dep[u] - dep[v];
    for(int x = 0; x < LOG; ++x) if(k>>x&1){
        u = up[u][x];
    }
    if(u == v) return u;
    for(int x = LOG - 1; x >= 0; --x) if(up[u][x] != up[v][x]){
        u = up[u][x];
        v = up[v][x];
    }
    assert(up[u][0] == up[v][0]);
    return up[u][0];
}

bool isAnsector(int p , int u){
    return in[u] >= in[p] && in[u] <= out[p];
}

// build the virtual tree adj list the root is vec[0] , keep the original version if you need it , clear virtual tree after each query
void virtualTree(vector<int>&vec) {
    int k = vec.size();
    sort(vec.begin() , vec.end() , [&](int x , int y){
        return in[x] < in[y];
    });

    for(int i = 1; i < k; ++i){
        vec.emplace_back(lca(vec[i-1] , vec[i]));
    }

    sort(vec.begin() , vec.end() , [&](int x , int y){
        return in[x] < in[y];
    });
    vec.erase(unique(vec.begin(),vec.end()),vec.end());

    stack<int> st;
    for(auto &x : vec){
        while(st.size() && !isAnsector(st.top() , x)) st.pop();
        if(st.size()){
            virtual_tree[st.top()].emplace_back(x);
        }
        st.push(x);
    }
}