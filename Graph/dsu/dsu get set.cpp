struct dsu{
    int n,cnt;
    vector<int>size,parent,nxt,tail,sets,pos;
    void init(int nn){
        this->n=nn;
        size.resize(n,1);
        parent.resize(n);
        nxt.resize(n,-1);
        sets.resize(n);
        pos.resize(n);
        tail.resize(n);
        iota(parent.begin(),parent.end(),0);
        iota(tail.begin(),tail.end(),0);
        iota(sets.begin(),sets.end(),0);
        iota(pos.begin(),pos.end(),0);
        cnt=nn;
    }
    dsu (int n=0){
        init(n);
    }
    int find(int child){
        return (child==parent[child]?child:parent[child]=find(parent[child]));
    }
    bool merge(int u,int v){
        u=find(u);
        v=find(v);
        if(v==u)return false;
        if(size[u]<size[v])swap(u,v);
        parent[v]=u;
        size[u]+=size[v];
        int p=pos[v];
        pos[sets[p]=sets[--cnt]]=p;
        int &t=tail[u];
        nxt[t]=v;
        t=tail[v];
        return true;

    }
    vector<int>get_set(int node){
        node=find(node);
        vector<int>res;
        for(int i=sets[node];~i;i=nxt[i]){
            res.emplace_back(i);
        }
        return  res;
    }
};
