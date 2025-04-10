int n,q;
const int K = 18;
int values[N],St[N],En[N],LinearTree[N],depth[N],parent[N],UP[K][N],qs[N],qe[N],qi[N],qlca[N],freq[N],comp[N],qt[N],Timer,en,st,nw[N],old[N],upIdx[N],nq,tim,CompSize;
vector<int>adj[N];
void dfs(int node,int par){
    parent[node] = par;
    depth[node] = (node == 0 ? 0 : depth[par] + 1);
    LinearTree[St[node] = Timer] = node;
    Timer++;
    for(auto &val:adj[node]){
        if(val == par)continue;
        dfs(val,node);
    }
    LinearTree[En[node] = Timer] = node;
    Timer++;
}
void build(){
    for(int i=0;i<n;i++){
        UP[0][i] = parent[i];
    }
    for(int i = 1 ;i < K;i++){
        for(int j=0;j<n;j++){
            UP[i][j] = UP[i-1][UP[i-1][j]];
        }
    }
}
int walk(int node,int kth){
    for(int i = 0;i<K;i++){
        if(kth & (1<<i)){
            node = UP[i][node];
        }
    }
    return node;
}
int Lca(int a,int b){
    if(depth[a] < depth[b])swap(a,b);
    a = walk(a,depth[a] - depth[b]);
    if(a == b)return a;
    for(int i = K - 1 ;i >= 0 ;i--){
        if(UP[i][a] != UP[i][b]){
            a = UP[i][a];
            b = UP[i][b];
        }
    }
    return parent[a];
}
int BlockSize,cnt,res[N];
void add(int value){
    cnt += !freq[value]++;
}
void remove(int value){
    cnt -= !--freq[value];
}
bool vis[N];
void upd(int MoIdx){
    vis[LinearTree[MoIdx]] ^= true;
    if(vis[LinearTree[MoIdx]])add(values[LinearTree[MoIdx]]);
    else remove(values[LinearTree[MoIdx]]);
}
int MoLeft = 0 , MoRight = -1;
bool in(int a,int l,int r){
    return a >= l && a <= r;
}
void update(int qId) {
    while (tim < qt[qId]) {
        tim++;
        bool f1 = in(St[upIdx[tim]], MoLeft, MoRight);
        bool f2 = in(En[upIdx[tim]], MoLeft, MoRight);
        if (f1 && !f2 || f2 && !f1) {
            remove(old[tim]);
            add(nw[tim]);
        }
        values[upIdx[tim]] = nw[tim];
    }
    while (tim > qt[qId]) {
        bool f1 = in(St[upIdx[tim]], MoLeft, MoRight);
        bool f2 = in(En[upIdx[tim]], MoLeft, MoRight);
        if (f1 && !f2 || f2 && !f1) {
            remove(nw[tim]);
            add(old[tim]);
        }
        values[upIdx[tim]] = old[tim];
        tim--;
    }
    while (MoRight < qe[qId]) upd(++MoRight);
    while (MoLeft > qs[qId]) upd(--MoLeft);
    while (MoRight > qe[qId]) upd(MoRight--);
    while (MoLeft < qs[qId]) upd(MoLeft++);
}

signed main() {
    khaled
    cin>>n>>q;
    for(int i=0;i<n;i++)cin>>values[i],comp[i] = values[i];
    for(int i=0;i<n-1;i++){
        int l,r;cin>>l>>r;
        l--,r--;
        adj[l].emplace_back(r);
        adj[r].emplace_back(l);
    }
    CompSize = n;
    dfs(0,0);build();
    for(int i=0;i<q;i++){
        int type;
        cin>>type;
        if(type == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (St[u] > St[v])swap(u, v);
            int s, e, L = Lca(u, v);
            if (L == u) {
                s = St[u] + 1;
            } else
                s = En[u];
            e = St[v];
            qs[nq] = s;
            qe[nq] = e;
            qi[nq] = nq;
            qlca[nq] = L;
            qt[nq] = tim;
            nq++;
        }else{
            int u,v;cin>>u>>v;
            tim++;
            u--;
            old[tim] = values[u];
            nw[tim] = v;
            values[u] = v;
            upIdx[tim] = u;
            comp[CompSize++] = v;
        }
    }
    BlockSize = ceil(pow(n,2.0/3.0) + 1);
    sort(comp , comp + CompSize);
    CompSize = unique(comp , comp + CompSize) - comp;
    for(int i=0;i<n;i++){
        values[i] = lower_bound(comp , comp + CompSize,values[i]) - comp;
    }
    for(int i = 1;i<=tim;i++){
        old[i] = lower_bound(comp , comp + CompSize, old[i]) - comp ;
        nw[i] = lower_bound(comp , comp + CompSize , nw[i]) - comp;
    }
    sort(qi,qi + nq , [](int a,int b) -> int{
        int bsa = qs[a] / BlockSize;
        int bea = qe[a] / BlockSize;
        int bsb = qs[b] / BlockSize;
        int beb = qe[b] / BlockSize;
        return tie(bsa,bea,qt[a]) < tie(bsb,beb,qt[b]);
    });
    for(int i=0;i<nq;i++){
        update(qi[i]);
        add(values[qlca[qi[i]]]);
        res[qi[i]] = cnt;
        remove(values[qlca[qi[i]]]);
    }
    for(int i=0;i<nq;i++){
        cout<<res[i]<<line;
    }
}

