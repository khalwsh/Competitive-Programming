const int k=26;
int binaryLifting[N][k];
vector<int>adj[N];
int parent[N];
int depth[N];

void MarkDepth(int node,int par,int c=0){
    depth[node]=c;
    for(auto &val:adj[node]){
        if(val!=par)MarkDepth(val,node,c+1);
    }
}

void build(int n){
    for(int i=0;i<n;i++)binaryLifting[i][0]=parent[i];
    for(int i=1;i<k;i++){
        for(int j=0;j<n;j++){
            binaryLifting[j][i]=binaryLifting[binaryLifting[j][i-1]][i-1];
        }
    }
}

int walk(int node,int kth){
    if(depth[node]<kth)return -1;
    for(int i=0;i<k;i++){
        if(kth&(1<<i))node=binaryLifting[node][i];
    }
    return node;
}

int lca(int a,int b){
    if(depth[a]>depth[b])a=walk(a,depth[a]-depth[b]);
    if(depth[b]>depth[a])b=walk(b,depth[b]-depth[a]);
    if(a==b)return b;
    for(int i=k-1;i>=0;i--){
        if(binaryLifting[a][i]!=binaryLifting[b][i]){
            a=binaryLifting[a][i];
            b=binaryLifting[b][i];
        }
    }
    return binaryLifting[a][0];
}

int dist (int a,int b){
    return depth[a]+depth[b]-2*depth[lca(a,b)];
}


int CalculateCommonNodesInPaths(int f, int s, int t){
    //s is source one
    //t is source two
    //f is the destination
    int ans = 0;
    bool is1 = lca(f, s) == f, is2 = lca(f, t) == f;
    if(is1 != is2)  return 1;
    if(is1)
        ans = max(ans, h[ lca(s, t) ] - h[ f ]);
    else if(lca(f, s) != lca(f, t))
        ans = max(ans, h[ f ] - max(h[ lca(f, s) ], h[ lca(f, t) ]));
    else
        ans = max(ans, h[ f ] + h[ lca(s, t) ] - 2 * h[ lca(f, t) ]);
    return ans + 1;
}
