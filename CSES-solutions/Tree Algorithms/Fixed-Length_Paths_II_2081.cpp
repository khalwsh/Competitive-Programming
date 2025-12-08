/* problem statement text */
/*
CSES - Fixed-Length Paths II

Time limit: 1.00 s
Memory limit: 512 MB

Given a tree of nnn nodes, your task is to count the number of distinct paths that have at least k1k_1k1​ and at most k2k_2k2​ edges.
Input
The first input line contains three integers nnn, k1k_1k1​ and k2k_2k2​: the number of nodes and the path lengths. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print one integer: the number of paths.
Constraints

1≤k1≤k2≤n≤2⋅1051 \le k_1 \le k_2 \le n \le 2 \cdot 10^51≤k1​≤k2​≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 2 3
1 2
2 3
3 4
3 5

Output:
6
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
int n, a, b;
vector<int> graph[200001];
int subtree[200001];
 
ll ans = 0, bit[200001];
int total_cnt[200001]{1}, mx_depth;
int cnt[200001], subtree_depth;
bool processed[200001];
 
int get_subtree_sizes(int node, int parent = 0) {
	subtree[node] = 1;
	for (int i : graph[node])
		if (!processed[i] && i != parent) subtree[node] += get_subtree_sizes(i, node);
	return subtree[node];
}
 
int get_centroid(int desired, int node, int parent = 0) {
	for (int i : graph[node])
		if (!processed[i] && i != parent && subtree[i] >= desired)
			return get_centroid(desired, i, node);
	return node;
}
 
void get_cnt(int node, int parent, int depth = 1) {
	if (depth > b) return;
	subtree_depth = max(subtree_depth, depth);
	cnt[depth]++;
	for (int i : graph[node])
		if (!processed[i] && i != parent) get_cnt(i, node, depth + 1);
}
 
void centroid_decomp(int node = 1) {
	int centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
	processed[centroid] = true;
	mx_depth = 0;
	long long partial_sum_init = (a == 1 ? 1ll : 0ll);
	for (int i : graph[centroid])
		if (!processed[i]) {
			subtree_depth = 0;
			get_cnt(i, centroid);
 
			long long partial_sum = partial_sum_init;
			for (int depth = 1; depth <= subtree_depth; depth++) {
				ans += partial_sum * cnt[depth];
 
				int dremove = b - depth;
				if (dremove >= 0) partial_sum -= total_cnt[dremove];
				int dadd = a - (depth + 1);
				if (dadd >= 0) partial_sum += total_cnt[dadd];
			}
 
			for (int depth = a - 1; depth <= b - 1 && depth <= subtree_depth; depth++)
				partial_sum_init += cnt[depth];
 
			for (int depth = 1; depth <= subtree_depth; depth++)
				total_cnt[depth] += cnt[depth];
			mx_depth = max(mx_depth, subtree_depth);
 
			fill(cnt, cnt + subtree_depth + 1, 0);
		}
	fill(total_cnt + 1, total_cnt + mx_depth + 1, 0);
	for (int i : graph[centroid])
		if (!processed[i]) centroid_decomp(i);
}
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> a >> b;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	centroid_decomp();
	cout << ans;
	return 0;
}