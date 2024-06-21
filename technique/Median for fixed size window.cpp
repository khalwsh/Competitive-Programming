struct BIT{
	int N;
	vector<ll>tree;
	void init(ll x){
		N=1<<x;
		tree.resize(this->N);
	}
	void add(int pos,ll value){
		for(++pos;pos<=N;pos+=pos&-pos)tree[pos-1]+=value;
	}
ll get(int pos){
	ll sum=0;
	for(++pos;pos>0;pos-=pos&-pos)sum+=tree[pos-1];
		return sum;
}
int find(ll t){
	int st=0;
	for(int sz=N>>1;sz;sz>>=1){
		if(tree[st+sz-1]<t){
			t-=tree[(st+=sz)-1];
		}
	}
	return st;
}
};
struct Multiset{
	BIT bit;
	Multiset(int x){
		bit.init(x);
		bit.add(0,-1);
	}
	int size(){
		return bit.get(bit.N-1)+1;
	}
	void insert(int value){
		bit.add(value,1);
	}
	void erase(int value){
		bit.add(value,-1);
	}
	int count(int x){
		return bit.get(x)-bit.get(x-1);
	}
	int at(int x){
		return bit.find(x);
	}
};
struct Fenwick{
	int n;
	vector<ll>tree;
	void init(int _n){
		n=_n;
		tree.resize(this->n);
	}
	void add(int pos,ll value){
		for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
	}
ll get(int pos) {
	ll sum = 0;
	for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
		return sum;
}
ll query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};

ll v[N] , comp[N];
signed main() {
	khaled
	int n,k;
	cin>>n>>k;
	for(int i = 0;i<n;i++){
		cin>>v[i];
		comp[i] = v[i];
	}
	sort(comp , comp + n);
	int s = unique(comp , comp + n) - comp;
	for(int i = 0;i<n;i++){
		v[i] = lower_bound(comp , comp + s , v[i]) - comp;
	}

	Multiset ms(19);
	Fenwick f , c;
	f.init(s + 10) , c.init(s + 10);
	for(int i=0;i<k;i++)ms.insert(v[i]) , f.add(v[i] , comp[v[i]]) , c.add(v[i] , 1);
	vector<ll>res;
	for(int i=0;i<n;i++){
		if(res.size()==n-k+1)break;
		int sz=ms.size();
		if(sz&1){
			ll meadian = ms.at((k+1)/2-1);
			res.emplace_back(c.query(0 , meadian) * comp[meadian] - f.query(0 , meadian) + (f.query(meadian , s + 9) - c.query(meadian , s + 9) * comp[meadian]));
		}else{
			ll meadian = max(ms.at((k)/2),ms.at((k)/2-1));
			res.emplace_back(c.query(0 , meadian) * comp[meadian] - f.query(0 , meadian) + (f.query(meadian , s + 9) - c.query(meadian , s + 9) * comp[meadian]));
		}
		f.add(v[i], -comp[v[i]]);
		c.add(v[i] , -1);
		f.add(v[i + k] , comp[v[i + k]]);
		c.add(v[i + k] , 1);
		ms.erase(v[i]);
		ms.insert(v[i+k]);
	}
	for(auto &val:res)cout<<val<<" ";
}