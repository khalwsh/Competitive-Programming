class SegmentTree{
    //you need to initialize the No-Operation variable before work
    //if it's assign make it -inf if it's add make it 0
    //1- make object , 2- initialize no-op 3- call init
public:
    vector<int>tree,lazy;
    int n;
    int No_Operation = 0;
    void init(int _n){
        n = _n;
        tree.resize(4*n);
        lazy.resize(4*n,No_Operation);
    }
private:
    void build(int node,int nl,int nr,vector<int>&v){
        if(nl==nr){
            tree[node]=v[nl];
            return;
        }
        int mid=nl+(nr-nl)/2;
        build(2*node+1,nl,mid,v);
        build(2*node+2,mid+1,nr,v);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void SingleUpdateAssign(int node,int nl,int nr,int ind,int newVal){
        //set the value;
        if(nl==nr&&nl==ind){
            tree[node] = newVal;
            return;
        }
        if(nl>ind||nr<ind)return;
        int mid=nl+(nr-nl)/2;
        SingleUpdateAssign(2*node+1,nl,mid,ind,newVal);
        SingleUpdateAssign(2*node+2,mid+1,nr,ind,newVal);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void PropAssign(int node,int nl,int nr){
        if(lazy[node]!=No_Operation){
            tree[node] = (nr-nl+1)*lazy[node];
            if(nl!=nr){
                lazy[2*node+1] = lazy[node];
                lazy[2*node+2] = lazy[node];
            }
            lazy[node]=No_Operation;
        }
    }
    void RangeUpdateAssign(int node,int nl,int nr,int l,int r,int newVal){
        PropAssign(node,nl,nr);
        if(nl>=l&&nr<=r){
            tree[node] = (nr-nl+1)*newVal;
            if(nl!=nr){
                lazy[2*node+1] = newVal;
                lazy[2*node+2] = newVal;
            }
            return;
        }
        if(nl>r||nr<l)return;
        int mid = nl+(nr-nl)/2;
        RangeUpdateAssign(2*node+1,nl,mid,l,r,newVal);
        RangeUpdateAssign(2*node+2,mid+1,nr,l,r,newVal);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void SingleUpdateAdd(int node,int nl,int nr,int ind,int Delta){
        //set the value;
        if(nl==nr&&nl==ind){
            tree[node] += Delta;
            return;
        }
        if(nl>ind||nr<ind)return;
        int mid=nl+(nr-nl)/2;
        SingleUpdateAdd(2*node+1,nl,mid,ind,Delta);
        SingleUpdateAdd(2*node+2,mid+1,nr,ind,Delta);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void PropAdd(int node,int nl,int nr){
        if(lazy[node]!=No_Operation){
            tree[node] += (nr-nl+1)*lazy[node];
            if(nl!=nr){
                lazy[2*node+1] += lazy[node];
                lazy[2*node+2] += lazy[node];
            }
            lazy[node]=No_Operation;
        }
    }
    void RangeUpdateAdd(int node,int nl,int nr,int l,int r,int Delta){
        PropAdd(node,nl,nr);
        if(nl>=l&&nr<=r){
            tree[node] += (nr-nl+1)*Delta;
            if(nl!=nr){
                lazy[2*node+1] += Delta;
                lazy[2*node+2] += Delta;
            }
            return;
        }
        if(nl>r||nr<l)return;
        int mid = nl+(nr-nl)/2;
        RangeUpdateAdd(2*node+1,nl,mid,l,r,Delta);
        RangeUpdateAdd(2*node+2,mid+1,nr,l,r,Delta);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    int QueryAdd(int node,int nl,int nr,int l,int r){
        PropAdd(node,nl,nr);
        if(nl>=l&&nr<=r)return tree[node];
        if(nl>r||nr<l)return 0;
        int mid=nl+(nr-nl)/2;
        return QueryAdd(2*node+1,nl,mid,l,r)+QueryAdd(2*node+2,mid+1,nr,l,r);
    }
    int QueryAssign(int node,int nl,int nr,int l,int r){
        PropAssign(node,nl,nr);
        if(nl>=l&&nr<=r)return tree[node];
        if(nl>r||nr<l)return 0;
        int mid=nl+(nr-nl)/2;
        return QueryAssign(2*node+1,nl,mid,l,r)+QueryAssign(2*node+2,mid+1,nr,l,r);
    }
public:
    void build(vector<int>&v){
        build(0,0,n-1,v);
    }
    void SingleUpdateAssign(int ind,int newVal){
        SingleUpdateAssign(0,0,n-1,ind,newVal);
    }
    void SingleUpdateAdd(int ind,int delta){
        SingleUpdateAdd(0,0,n-1,ind,delta);
    }
    void RangeUpdateAdd(int l,int r,int delta){
        RangeUpdateAdd(0,0,n-1,l,r,delta);
    }
    void RangeUpdateAssign(int l,int r,int newVal){
        RangeUpdateAssign(0,0,n-1,l,r,newVal);
    }
    int QueryAdd(int l,int r){
        return QueryAdd(0,0,n-1,l,r);
    }
    int QueryAssign(int l,int r){
        return QueryAssign(0,0,n-1,l,r);
    }
};