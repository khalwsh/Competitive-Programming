const int N = 2e5 + 10;
int n, m;
set<int> adj[N];
int degree[N];
vector<int> tour;

void dfs(int node){
    while(!adj[node].empty()){
        auto it = adj[node].begin();
        int x = *it;
        adj[node].erase(it);
        if(adj[x].erase(node)){
            dfs(x);
        }
    }
    tour.emplace_back(node);
}

bool check(){
    int odd = 0;
    for(int i = 0; i < n; ++i){
        if(degree[i] & 1) ++odd;
    }
    return (odd == 0 || odd == 2);
}

bool get(){
    if(!check()) return false;
    int start = -1;
    for(int i = 0; i < n; ++i){
        if(degree[i] & 1){ start = i; break; }
    }
    if(start == -1){
        for(int i = 0; i < n; ++i){
            if(degree[i] > 0){ start = i; break; }
        }
    }

    if(start == -1){
        return (m == 0);
    }

    tour.clear();
    dfs(start);
    reverse(tour.begin(), tour.end());

    if((int)tour.size() != m + 1) return false;
    return true;
}