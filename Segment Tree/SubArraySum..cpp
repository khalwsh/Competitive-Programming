struct Node{
//note min sum = 0
	int MAXLEFT,MAXRIGHT,MAX,SUM;
	Node(int a=0,int b=0,int c=0,int d=0){
		SUM=a,MAXLEFT=b,MAXRIGHT=c,MAX=d;
	}

	Node operator+(const Node&a){
		Node res;
		res.SUM=a.SUM+SUM;
		res.MAXLEFT=max(MAXLEFT,SUM+a.MAXLEFT);
		res.MAXRIGHT=max(a.MAXRIGHT,a.SUM+MAXRIGHT);
		res.MAX=max({MAX,a.MAX,MAXRIGHT+a.MAXLEFT});
		return res;
	}

};
struct SegmentTree{
	vector<Node>tree;vector<int>lazy;
	int n;
	SegmentTree(int _n){

		n=_n;
		tree.resize(4*n);
        lazy.resize(4*n,-inf);

	}
	void build(int node,int nl,int nr,vector<int>&v){

		if(nl==nr){
			tree[node]=Node(v[nl],v[nl],v[nl],v[nl]);
			return;
		}
		int mid=nl+(nr-nl)/2;
		build(2*node+1,nl,mid,v);
		build(2*node+2,mid+1,nr,v);
		tree[node]=tree[2*node+1]+tree[2*node+2];
	}
    void prop(int node,int nl,int nr){
        if(lazy[node]!=-inf){
            int val = (nr-nl+1)*lazy[node];
            tree[node]=Node(val,val,val,val);
            if(nl!=nr){
                lazy[node*2+1]=lazy[node];
                lazy[node*2+2]=lazy[node];
            }
            lazy[node]=-inf;
        }
    }
	void update(int node,int nl,int nr,int l,int r,int newValue){
        prop(node,nl,nr);
        if(nl>=l&&nr<=r){
            int val = (nr-nl+1) * newValue;
            tree[node]=Node(val,val,val,val);
            if(nl!=nr){
                lazy[node*2+1]=newValue;
                lazy[node*2+2]=newValue;
            }
            return ;
        }
        if(nl>r||nr<l)return;
        int mid = nl+(nr-nl)/2;
        update(2*node+1,nl,mid,l,r,newValue);
        update(2*node+2,mid+1,nr,l,r,newValue);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
	Node query(int node,int nl,int nr,int l,int r){
        prop(node,nl,nr);
		if(nl>=l&&nr<=r)return tree[node];
		if(nl>r||nr<l)return Node();
		int mid=nl+(nr-nl)/2;
		return query(2*node+1,nl,mid,l,r)+query(2*node+2,mid+1,nr,l,r);
	}
};