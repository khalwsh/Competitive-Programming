struct twosat {
	int n;  // total size combining +, -. must be even.
	vector< vector<int> > g, gt;
	vector<bool> vis, res;
	vector<int> comp;
	stack<int> ts;
	twosat(int vars = 0) {
		n = vars << 1;
		g.resize(n);
		gt.resize(n);
	}

	//zero indexed, be careful
	//if you want to force variable a to be true in OR or XOR combination
	//add addOR (a,1,a,1);
	//if you want to force variable a to be false in OR or XOR combination
	//add addOR (a,0,a,0);

	//(x_a or (not x_b))-> af=1,bf=0
	void addOR(int a, bool af, int b, bool bf) {
		a += a + (af ^ 1);
		b += b + (bf ^ 1);
		g[a ^ 1].push_back(b);  // !a => b
		g[b ^ 1].push_back(a);  // !b => a
		gt[b].push_back(a ^ 1);
		gt[a].push_back(b ^ 1);
	}
	//(!x_a xor !x_b)-> af=0, bf=0
	void addXOR(int a, bool af, int b, bool bf) {
		addOR(a, af, b, bf);
		addOR(a, !af, b, !bf);
	}
	void _add(int a,bool af,int b,bool bf) {
		a += a + (af ^ 1);
		b += b + (bf ^ 1);
		g[a].push_back(b);
		gt[b].push_back(a);
	}
	//add this type of condition->
	//add(a,af,b,bf) means if a is af then b must need to be bf
	void add(int a,bool af,int b,bool bf) {
		_add(a, af, b, bf);
		_add(b, !bf, a, !af);
	}
	void dfs1(int u) {
		vis[u] = true;
		for(int v : g[u]) if(!vis[v]) dfs1(v);
		ts.push(u);
	}
	void dfs2(int u, int c) {
		comp[u] = c;
		for(int v : gt[u]) if(comp[v] == -1) dfs2(v, c);
	}
	bool ok() {
		vis.resize(n, false);
		for(int i = 0; i < n; ++i) if(!vis[i]) dfs1(i);
		int scc = 0;
		comp.resize(n, -1);
		while(!ts.empty()) {
			int u = ts.top();
			ts.pop();
			if(comp[u] == -1) dfs2(u, scc++);
		}
		res.resize(n / 2);
		for(int i = 0; i < n; i += 2) {
			if(comp[i] == comp[i + 1]) return false;
			res[i / 2] = (comp[i] > comp[i + 1]);
		}
		return true;
	}
};