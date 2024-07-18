struct Node{
    int left,right;
    bool alter;
    Node (int l=0,int r=0,bool a=false){
        left = l;
        right = r;
        alter = a;
    }
    Node operator+(const Node & b){
        Node res;
        res.left =  left;
        res.right = b.right;
        res.alter = alter && b.alter && (right!=b.left);
        return res;
    }
};
struct Segment{
    int n;
    vector<Node>tree;
    vector<int>lazy;
    Segment(int _n){
        n = _n;
        tree.resize(n*4);
        lazy.resize(4*n);
    }
    void build(int node,int nl,int nr , string &s){
        if(nl==nr){
            tree[node]=Node(s[nl]-'0',s[nl]-'0',true);
            return;
        }
        int mid = nl+(nr - nl)/2;
        build(2*node+1,nl,mid , s);
        build(2*node+2,mid+1,nr , s);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void prop(int node,int nl,int nr){
        if(lazy[node]){
            tree[node].left ^=1;
            tree[node].right ^=1;
            if(nl!=nr){
                lazy[2*node+1]^=true;
                lazy[2*node+2]^=true;
            }
            lazy[node]=false;
        }
    }
    void update(int node,int nl,int nr,int l,int r){
        prop(node,nl,nr);
        if(nl>=l&&nr<=r){
            tree[node].left ^=1;
            tree[node].right ^=1;
            if(nl!=nr){
                lazy[2*node+1]^=true;
                lazy[2*node+2]^=true;
            }
            return;
        }
        if(nr<l||nl>r)return;
        int mid = nl+(nr-nl)/2;
        update(2*node+1,nl,mid,l,r);
        update(2*node+2,mid+1,nr,l,r);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    Node query(int node,int nl,int nr,int l,int r){
        prop(node,nl,nr);
        if(nl>=l&&nr<=r){
            return tree[node];
        }
        int mid = nl+(nr-nl)/2;
        if(r<=mid)return query(2*node+1,nl,mid,l,r);
        if(l>=mid+1)return query(2*node+2,mid+1,nr,l,r);
        return query(2*node+1,nl,mid,l,r)+ query(2*node+2,mid+1,nr,l,r);
    }
};