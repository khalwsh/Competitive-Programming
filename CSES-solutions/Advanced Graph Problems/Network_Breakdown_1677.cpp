/* problem statement text */
/*
CSES - Network Breakdown

Time limit: 1.00 s
Memory limit: 512 MB

Syrjälä's network has nnn computers and mmm connections between them. The network consists of components of computers that can send messages to each other.
Nobody in Syrjälä understands how the network works. For this reason, if a connection breaks down, nobody will repair it. In this situation a component may be divided into two components.
Your task is to calculate the number of components after each connection breakdown.
Input
The first input line has three integers nnn, mmm and kkk: the number of computers, connections and breakdowns. The computers are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the connections. Each line has two integers aaa and bbb: there is a connection between computers aaa and bbb. Each connection is between two different computers, and there is at most one connection between two computers.
Finally, there are kkk lines describing the breakdowns. Each line has two integers aaa and bbb: the connection between computers aaa and bbb breaks down.
Output
After each breakdown, print the number of components.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤k≤m1 \le k \le m1≤k≤m
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 5 3
1 2
1 3
2 3
3 4
4 5
3 4
2 3
4 5

Output:
2 2 3
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
    int n ,m , q; cin >> n >> m >> q;
    map<pair<int , int> , int> qi;
    vector<array<int , 3>> e;
    for (int i = 0;i < m;i++) {
        int u , v; cin >> u >> v;
        u-- , v--;
        e.emplace_back(array<int , 3>{u , v , q + 10});
    }
    for (int i = 0;i < q;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        qi[{u , v}] = qi[{v , u}] = i + 1;
    }
    for (auto &val : e) {
        if (qi.count({val[0] , val[1]})) {
            val[2] = qi[{val[0] , val[1]}];
        }
    }
    sort(e.begin() , e.end() , [&](array<int , 3> &a , array<int , 3> &b) -> bool {
        int i1 = a[2];
        int i2 = b[2];
        return i1 < i2;
    });
    dsu d(n);
    vector<int> res;
    for (int j = e.size() - 1;j >= 0;j--) {
        if (e[j][2] < q + 10) {
            res.emplace_back(d.cnt);
        }
        d.merge(e[j][0] , e[j][1]);
    }
    reverse(res.begin() , res.end());
    for (auto &val : res) cout << val << " ";
}