/* problem statement text */
/*
CSES - Eulerian Subgraphs

Time limit: 1.00 s
Memory limit: 512 MB

You are given an undirected graph that has nnn nodes and mmm edges.
We consider subgraphs that have all nodes of the original graph and some of its edges. A subgraph is called Eulerian if each node has even degree.
Your task is to count the number of Eulerian subgraphs modulo 109+710^9+7109+7.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines that describe the edges. Each line has two integers aaa and bbb: there is an edge between nodes aaa and bbb. There is at most one edge between two nodes, and each edge connects two distinct nodes.
Output
Print the number of Eulerian subgraphs modulo 109+710^9+7109+7.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
0≤m≤2⋅1050 \le m \le 2 \cdot 10^50≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 3
1 2
1 3
2 3

Output:
2

Explanation: You can either keep or remove all edges, so there are two possible Eulerian subgraphs.
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
struct dsu{
    int n,cnt;
    vector<int>size,parent;
    void init(int nn){
        this->n=nn;
        size.resize(n,1);
        parent.resize(n);
        iota(parent.begin(),parent.end(),0);
        cnt=nn;
    }
    dsu (int n=0){
        init(n);
    }
    int find(int child){
        return (child==parent[child]?child:parent[child]=find(parent[child]));
    }
    bool merge(int u,int v){
        u=find(u);
        v=find(v);
        if(v==u)return false;
        if(size[u]<size[v])swap(u,v);
        parent[v]=u;
        size[u]+=size[v];
        cnt--;
        return true;
 
    }
};
 
const int mod = 1e9 + 7;
ll fp(ll a , ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
 
int main() {
    PRE();
    int n , m; cin >> n >> m;
    dsu d(n);
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        d.merge(u , v);
    }
    cout << fp(2 , m - n + d.cnt) << '\n';
}