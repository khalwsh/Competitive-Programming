/* problem statement text */
/*
CSES - Giant Pizza

Time limit: 1.00 s
Memory limit: 512 MB

Uolevi's family is going to order a large pizza and eat it together. A total of nnn family members will join the order, and there are mmm possible toppings. The pizza may have any number of toppings.
Each family member gives two wishes concerning the toppings of the pizza. The wishes are of the form "topping xxx is good/bad". Your task is to choose the toppings so that at least one wish from everybody becomes true (a good topping is included in the pizza or a bad topping is not included).
Input
The first input line has two integers nnn and mmm: the number of family members and toppings. The toppings are numbered 1,2,…,m1,2,\dots,m1,2,…,m.
After this, there are nnn lines describing the wishes. Each line has two wishes of the form "+ xxx" (topping xxx is good) or "- xxx" (topping xxx is bad).
Output
Print a line with mmm symbols: for each topping "+" if it is included and "-" if it is not included. You can print any valid solution.
If there are no valid solutions, print "IMPOSSIBLE".
Constraints

1≤n,m≤1051 \le n,m \le 10^51≤n,m≤105
1≤x≤m1 \le x \le m1≤x≤m

Example
Input:
3 5
+ 1 + 2
- 1 + 3
+ 4 - 2

Output:
- + + + -
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
template<class E>
struct csr {
	std::vector<int> start;
	std::vector<E> elist;
 
	explicit csr(int n, const std::vector<std::pair<int, E>> &edges)
	: start(n + 1), elist(edges.size()) {
		for (auto e: edges) {
			start[e.first + 1]++;
		}
		for (int i = 1; i <= n; i++) {
			start[i] += start[i - 1];
		}
		auto counter = start;
		for (auto e: edges) {
			elist[counter[e.first]++] = e.second;
		}
	}
};
struct scc_graph {
public:
	explicit scc_graph(int n) : _n(n) {}
 
	int num_vertices() { return _n; }
 
	void add_edge(int from, int to) { edges.push_back({from, {to}}); }
 
    // @return pair of (# of scc, scc id)
	std::pair<int, std::vector<int>> scc_ids() {
		auto g = csr<edge>(_n, edges);
		int now_ord = 0, group_num = 0;
		std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
		visited.reserve(_n);
		auto dfs = [&](auto self, int v) -> void {
			low[v] = ord[v] = now_ord++;
			visited.push_back(v);
			for (int i = g.start[v]; i < g.start[v + 1]; i++) {
				auto to = g.elist[i].to;
				if (ord[to] == -1) {
					self(self, to);
					low[v] = std::min(low[v], low[to]);
				} else {
					low[v] = std::min(low[v], ord[to]);
				}
			}
			if (low[v] == ord[v]) {
				while (true) {
					int u = visited.back();
					visited.pop_back();
					ord[u] = _n;
					ids[u] = group_num;
					if (u == v) break;
				}
				group_num++;
			}
		};
		for (int i = 0; i < _n; i++) {
			if (ord[i] == -1) dfs(dfs, i);
		}
		for (auto &x: ids) {
			x = group_num - 1 - x;
		}
		return {group_num, ids};
	}
 
	std::vector<std::vector<int>> scc() {
		auto ids = scc_ids();
		int group_num = ids.first;
		std::vector<int> counts(group_num);
		for (auto x: ids.second) counts[x]++;
			std::vector<std::vector<int>> groups(ids.first);
		for (int i = 0; i < group_num; i++) {
			groups[i].reserve(counts[i]);
		}
		for (int i = 0; i < _n; i++) {
			groups[ids.second[i]].push_back(i);
		}
		return groups;
	}
 
private:
	int _n;
	struct edge {
		int to;
	};
	std::vector<std::pair<int, edge>> edges;
};
struct two_sat {
public:
	two_sat() : _n(0), scc(0) {}
 
	explicit two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}
 
	void OR(int i, bool f, int j, bool g) {
		assert(0 <= i && i < _n);
		assert(0 <= j && j < _n);
		scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
		scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
	}
	void Xor(int a, bool f , int b , bool g){
		OR(a , f , b , g);
		OR(a , !f , b , !g);
	}
	void Imply(int a, bool f , int b , bool g){
		OR(a , !f , b , g);
	}
	void BiImply(int a,bool f , int b , bool g){
		// equivalent to Xnor
		Imply(a ,f , b ,g);
		Imply(b ,f  ,a ,g);
	}
	void ForceTrue(int a){
		OR(a , true , a , true);
	}
	void ForceFalse(int a){
		OR(a , false ,a , false);
	}
 
	bool satisfiable() {
		auto id = scc.scc_ids().second;
		for (int i = 0; i < _n; i++) {
			if (id[2 * i] == id[2 * i + 1]) return false;
			_answer[i] = id[2 * i] < id[2 * i + 1];
		}
		return true;
	}
 
	std::vector<bool> answer() { return _answer; }
 
private:
	int _n;
	std::vector<bool> _answer;
	scc_graph scc;
};
int main() {
    PRE();
	int n , m;cin >> n >> m;
	two_sat sat(m);
	for (int i = 0;i < n;i++) {
		char ch;cin >> ch;
		int x;cin >> x;
		char ch2; cin >> ch2;
		int y;cin >> y;
		x-- , y--;
		sat.OR(x , ch == '+' , y , ch2 == '+');
	}
	if (sat.satisfiable()) {
		auto s = sat.answer();
		for (int i = 0;i < m;i++) {
			if (s[i]) cout << '+';
			else cout << "-";
			cout << " ";
		}
	}else {
		cout << "IMPOSSIBLE";
	}
}