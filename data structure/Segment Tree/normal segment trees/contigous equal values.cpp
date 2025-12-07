struct Node{
	int best , len;
	int pref_t , pref_sz;
	int suf_t , suf_sz;
	Node(){
		best = 0; len = 0;
		pref_t = suf_t = -1;
		pref_sz = suf_sz = 0;
	}
	Node(int x){
		best = 1 , len = 1;
		pref_t = suf_t = x;
		pref_sz = suf_sz = 1;
	}
};
Node operator+(const Node &a , const Node &b){
	if(a.suf_t == -1) return b;
	if(b.pref_t == -1) return a;

	Node res;
	res.best = max(a.best , b.best);
	res.len = a.len + b.len;
	res.pref_t = a.pref_t;
	res.suf_t = b.suf_t;

	res.pref_sz = a.pref_sz + ((a.pref_sz == a.len && a.suf_t == b.pref_t) ? b.pref_sz : 0);
	res.suf_sz = b.suf_sz + ((b.suf_sz == b.len && b.pref_t == a.suf_t) ? a.suf_sz : 0);

	if(a.suf_t == b.pref_t) res.best = max(res.best , a.suf_sz + b.pref_sz);

	return res;
}
struct SegmentTree {
	vector<Node> tree;
	int n;
	SegmentTree(int n_) {
		n = n_;
		if (n > 0) tree.assign(4 * n, Node());
		else tree.clear();
	}
	void update_point(int idx, int val) {
		if (idx < 0 || idx >= n) return; 
		update_point(0, 0, n - 1, idx, val);
	}
	void update_point(int x, int l, int r, int idx, int val) {
		if (l == r) {
			tree[x] = Node(val);
			return;
		}
		int mid = (l + r) >> 1;
		if (idx <= mid) update_point(2 * x + 1, l, mid, idx, val);
		else update_point(2 * x + 2, mid + 1, r, idx, val);
		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}
	Node query(int ql, int qr) {
		if (ql > qr) return Node();
		ql = max(0, ql);
		qr = min(n - 1, qr);
		if (ql > qr) return Node();
		return query(0, 0, n - 1, ql, qr);
	}

	Node query(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return tree[x];
		if (r < ql || l > qr) return Node(); 
		int mid = (l + r) >> 1;
		return query(2 * x + 1, l, mid, ql, qr) + query(2 * x + 2, mid + 1, r, ql, qr);
	}
};