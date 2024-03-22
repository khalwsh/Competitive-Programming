struct Node{
        int a,b,c;
        Node(){
            a=b=c=0;
        }
        Node operator+(Node&x){
            Node z;
            int t=min(b,x.c);
            z.a=a+x.a+t;
            z.b=b+x.b-t;
            z.c=c+x.c-t;
            return z;
        }
    };

struct segment_tree{
    vector<Node>tree;
    int n;
    segment_tree(int n){
        this->n=n;
        tree.resize(this->n*4);
    }
    void build(int node,int nl,int nr,string& s){
        if(nl==nr){
            if(s[nl]=='(')tree[node].b=1;
            else tree[node].c=1;
            return;
        }
        int mid=nl+(nr-nl)/2;
        build(2*node+1,nl,mid,s);
        build(2*node+2,mid+1,nr,s);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    Node query(int node,int nl,int nr,int l,int r){
        if(nl>r||nr<l)return Node();
        if(nl>=l&&nr<=r){
            return tree[node];
        }
        int mid=nl+(nr-nl)/2;
        Node left=query(2*node+1,nl,mid,l,r);
        Node right=query(2*node+2,mid+1,nr,l,r);
        return left+right;
    }
};