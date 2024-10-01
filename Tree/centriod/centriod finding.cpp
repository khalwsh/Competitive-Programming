vector<int>adj[N];
int siz[N];
bool removed[N];
void Size(int node , int par) {
    siz[node] = 1;
    for(auto &val:adj[node]) {
        if(val == par || removed[val])continue;
        Size(val , node);
        siz[node] += siz[val];
    }
}
int Centriod(int node , int par , int s) {
    for(auto &val:adj[node]) {
        if(val == par || removed[val])continue;
        if(siz[val] > s / 2) {
            return Centriod(val , node , s);
        }
    }
    return node;
}
bool fail = false;
void decomp(int node) {
    Size(node , -1);
    int cen = Centriod(node , -1 , siz[node]);
    removed[cen] = true;
    // cen is the centriod
    for(auto &val:adj[cen]) {
        if(removed[val])continue;
        decomp(val);
    }
}