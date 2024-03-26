vector<int> adj[N];
vector<int> euler_tour;
int n;
int in[4 * N] , Timer = 0;
void dfs(int u = 0 , int p = 0){
    in[u] = Timer++;
    euler_tour.emplace_back(u);
    for(auto &v : adj[u]) if(v != p){
            dfs(v , u);
            euler_tour.emplace_back(u);
            Timer++;
        }
}
struct SparseTable {
    vector<int> log;
    vector<vector<pair<int, int>>> spt;
    void init(int _n) {
        int k = 20;
        spt = vector<vector<pair<int, int>>>(k, vector<pair<int, int>>(_n));
        for (int i = 0; i < _n; i++) {
            spt[0][i] = { in[euler_tour[i]] , euler_tour[i] };
        }
        for (int j = 1; 1 << j <= _n; j++) {
            for (int i = 0; i + (1 << j) - 1 < _n; i++) {
                spt[j][i] = merge(spt[j - 1][i], spt[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    pair<int, int> merge(pair<int, int> &x, pair<int, int> &y) {
        if(x.first < y.first) return x;
        return y;
    }
    pair<int, int> query(int i, int j) {
        int len = j - i + 1;
        int k = log2_floor(len);
        return merge(spt[k][i], spt[k][j - (1 << k) + 1]);
    }
    int LCA(int i , int j){
        if(in[i] > in[j]) swap(i , j);
        return query(in[i] , in[j]).second;
    }
};
SparseTable spt;
void build(){
    dfs();
    spt.init(Timer);
}