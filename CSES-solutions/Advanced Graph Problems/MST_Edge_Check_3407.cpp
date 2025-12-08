/* problem statement text */
/*
CSES - MST Edge Check

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected weighted graph, determine for each edge if it can be included in a minimum spanning tree.
Input
The first line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The following mmm lines describe the edges. Each line has three integers aaa, bbb, www: there is an edge between nodes aaa and bbb with weight www.
You can assume that the graph is connected and simple and each edge appears at most once in the graph.
Output
For each edge in the input order, print YES if it can be included in the minimum spanning tree and NO otherwise.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤w≤1091 \le w \le 10^91≤w≤109

Example
Input:
5 6
1 2 4
1 3 2
2 4 2
3 4 1
3 5 3
4 5 3

Output:
NO
YES
YES
YES
YES
YES
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
    vector<int>size,parent,nxt,tail,sets,pos;
    void init(int nn){
        this->n=nn;
        size.resize(n,1);
        parent.resize(n);
        nxt.resize(n,-1);
        sets.resize(n);
        pos.resize(n);
        tail.resize(n);
        iota(parent.begin(),parent.end(),0);
        iota(tail.begin(),tail.end(),0);
        iota(sets.begin(),sets.end(),0);
        iota(pos.begin(),pos.end(),0);
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
        int p=pos[v];
        pos[sets[p]=sets[--cnt]]=p;
        int &t=tail[u];
        nxt[t]=v;
        t=tail[v];
        return true;
 
    }
    vector<int>get_set(int node){
        node=find(node);
        vector<int>res;
        for(int i=sets[node];~i;i=nxt[i]){
            res.emplace_back(i);
        }
        return  res;
    }
};
 
int main() {
    PRE();
    int n , m; cin >> n >> m;
    vector<array<int , 4>> e(m);
    int idx = 0;
    for (auto &[u , v , w , i] : e) cin >> u >> v >> w , i = idx++ , u-- , v--;
    sort(e.begin() , e.end() , [&](array<int , 4> &a , array<int , 4> &b) -> bool {
        return a[2] < b[2];
    });
    vector<int> ws;
    for (auto &[u , v , w , i] : e) {
        if (ws.empty() || ws.back() != w) ws.emplace_back(w);
    }
    int i = 0;
    dsu d(n);
    vector<bool> res(m);
    for (auto &val : ws) {
        vector<pair<int , int>> to_connect;
        while (e[i][2] <= val) {
            if (d.find(e[i][0]) == d.find(e[i][1])) {
                // not a mst edge
            }else {
                res[e[i][3]] = true;
            }
            to_connect.emplace_back(e[i][0] , e[i][1]);
            i++;
        }
        for (auto &[u , v] : to_connect) d.merge(u , v);
    }
    for (i = 0;i < m;i++) cout << (res[i] ? "YES" : "NO") << '\n';
}