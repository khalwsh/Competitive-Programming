struct node{
    vector<int>v;
    node operator+(const node&a2){
        node res;
        int p1=0,p2=0;
        while(p1<v.size()&&p2<a2.v.size()){
            if(v[p1]<a2.v[p2])res.v.emplace_back(v[p1]),p1++;
            else res.v.emplace_back(a2.v[p2]),p2++;
        }
        while(p1<v.size())res.v.emplace_back(v[p1]),p1++;
        while(p2<a2.v.size())res.v.emplace_back(a2.v[p2]),p2++;
        return res;
    }
    void merge(const node&a,const node&b){
        std::merge(a.v.begin(),a.v.end(),b.v.begin(),b.v.end(),inserter(v,v.begin()));

    }
};
struct SegmentTree{
    vector<node>tree;
    int n;
    SegmentTree(int n){
        this->n=n;
        tree.resize(n*4);
    }
    void build(int nd,int nl,int nr,vector<int>&v){
        if(nl==nr){
            tree[nd].v.emplace_back(v[nl]);
            return;
        }
        int mid=nl+(nr-nl)/2;
        build(2*nd+1,nl,mid,v);
        build(2*nd+2,mid+1,nr,v);
        tree[nd].merge(tree[2*nd+1],tree[2*nd+2]);
    }
    int query(int nd,int nl,int nr,int l,int r,int value){
        if(nl>r||nr<l)return 0;
        if(nl>=l&&nr<=r)return lower_bound(tree[nd].v.begin(),tree[nd].v.end(),value)-tree[nd].v.begin();
        int mid=nl+(nr-nl)/2;
        return query(2*nd+1,nl,mid,l,r,value)+query(2*nd+2,mid+1,nr,l,r,value);
    }
};
