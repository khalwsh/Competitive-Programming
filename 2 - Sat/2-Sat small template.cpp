struct two_sat {
    int n, cur_comp = 0;
    vector<vector<int>> adj, adjr;
    vector<int> order, comp, val;
    two_sat(int n) : n(2 * n), adj(2 * n), adjr(2 * n), comp(2 * n) {}
    void OR(int a, int sa, int b, int sb) { 
        int pa = (2 * a) ^ sa, pb = (2 * b) ^ sb;
        adj[pa ^ 1].push_back(pb);
        adj[pb ^ 1].push_back(pa);
        adjr[pb].push_back(pa ^ 1);
        adjr[pa].push_back(pb ^ 1);
    }
 
    void Xor(int a, int sa, int b, int sb) {
        OR(a, sa, b, sb);
        OR(a, sa ^ 1, b, sb ^ 1);
    }
 
    void Imply(int a, int sa, int b, int sb){
        OR(a, sa ^ 1, b, sb);
    }
    void BiImply(int a, bool f , int b , bool g){
    	Imply(a , f , b ,g);
    	Imply(b , g , a , f);
    }
 
    void dfs1(int v) {
        comp[v] = 1;
        for (int ch : adj[v]) if (!comp[ch]) dfs1(ch);
        order.push_back(v);
    }
    void dfs2(int v) {
        comp[v] = cur_comp;
        for (int ch : adjr[v]) if (!comp[ch]) dfs2(ch);
    }
    bool satisfiable() {
        for (int i = 0; i < n; i++) if (!comp[i]) dfs1(i);
        reverse(order.begin(), order.end());
        comp = vector<int>(n);
        for (int v : order) if (!comp[v]) {
            cur_comp++;
            dfs2(v);
        }
        val = vector<int>(n / 2, -1);
        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i ^ 1]) return false;
            val[i / 2] = comp[i] > comp[i ^ 1];
        }
        return true;
    }
    vector<int>answer(){
    	return val;
    }
};