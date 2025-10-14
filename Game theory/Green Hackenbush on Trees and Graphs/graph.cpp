
/**
Consider a two player game on a graph with a specified vertex (root).
In each turn, a player eliminates one edge.
Then, if a subgraph that is disconnected from the root, it is removed.
If a player cannot select an edge (i.e., the graph is singleton),
he will lose.
Compute the Grundy number of the given graph.

We will use two principles:
1. Colon Principle:
    Grundy number of a tree is the xor of
    Grundy number of child subtrees.

2. Fusion Principle:
    Consider a pair of adjacent vertices u, v
    that has another path (i.e., they are in a cycle). Then,
    we can contract u and v without changing Grundy number.

We first decompose graph into two-edge connected components.
Then, by contracting each components by using Fusion Principle,
we obtain a tree (and many self loops) that has the same Grundy
number to the original graph. By using Colon Principle, we can
compute the Grundy number.

Complexity: O(m + n).

Verified:
SPOJ 1477: Play with a Tree
IPSC 2003 G: Got Root?
**/

// if there is self cycle , u - u then ans ^= 1 for each self loop
const int N = 2e5 + 10;
vector<int> g[N];
int n, T, low[N], dis[N];

int dfs(int u, int pre = 0) {
    dis[u] = low[u] = ++T;
    int ans = 0;
    for (auto v: g[u]) {
        if (v == pre) {
            pre += 2 * n;
            continue;
        }
        if (dis[v] == 0) {
            int res = dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dis[u])
                ans ^= (1 + res) ^ 1; /// bridge
            else
                ans ^= res; /// non bridge
        } else low[u] = min(low[u], dis[v]);
    }
    if (pre > n) pre -= 2 * n;
    for (auto v: g[u]) if (v != pre && dis[u] <= dis[v]) ans ^= 1;
    return ans;
}
