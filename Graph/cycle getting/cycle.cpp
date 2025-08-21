const int N = 5e5 + 10;
vector<int>adj[N];
int n;
 
vector<bool>visited;
vector<int>parent;
int cycle_start , cycle_end;
 
bool dfs(int v , int par){
	visited[v] = true;
	for(auto &u : adj[v]){
		if(u == par)continue;
		if(visited[u]){
			cycle_end = v;
			cycle_start = u;
			return true;
		}
		parent[u] = v;
		if(dfs(u , v)) return true;
	}
	return false;
}
vector<int> get_cycle(){
	visited.assign(n , false);
	parent.assign(n , -1);
	cycle_start = -1;
	for(int i = 0;i < n;i++){
		if(!visited[i] && dfs(i , parent[i])){
			break;
		}
	}
	assert(cycle_start != -1);
	vector<int>res;
	res.push_back(cycle_start);
	for(int v = cycle_end; v != cycle_start;v = parent[v]){
		res.push_back(v);
	}
	res.emplace_back(cycle_start);
	return res;
}