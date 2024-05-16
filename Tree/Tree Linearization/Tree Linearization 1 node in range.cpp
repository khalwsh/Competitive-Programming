int LinearTree[2*N],ST[N],EN[N],Timer = 0;
vector<int>adj[N];
void Linear(int node,int par) {
    LinearTree[Timer] = node;
    ST[node] = Timer;
    Timer++;
    for (auto &val: adj[node]) {
        if (val == par)continue;
        Linear(val, node);
    }
    EN[node] = Timer - 1;
}