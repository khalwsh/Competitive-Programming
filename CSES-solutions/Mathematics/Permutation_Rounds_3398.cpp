/* problem statement text */
/*
CSES - Permutation Rounds

Time limit: 1.00 s
Memory limit: 512 MB

There is a sorted array [1,2,…,n][1,2,\dots,n][1,2,…,n] and a permutation p1,p2,…,pnp_1,p_2,\dots,p_np1​,p2​,…,pn​. On each round, all elements move according to the permutation: the element at position iii moves to position pip_ipi​.
After how many rounds is the array sorted again for the first time?
Input
The first line has an integer nnn.
The next line contains nnn integers p1,p2,…,pnp_1,p_2,\dots,p_np1​,p2​,…,pn​.
Output
Print the number of rounds modulo 109+710^9+7109+7.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105

Example
Input:
8
5 3 2 6 4 1 8 7

Output:
4

Explanation: The array changes as follows after the rounds:

Round 1: [6,3,2,5,1,4,8,7][6,3,2,5,1,4,8,7][6,3,2,5,1,4,8,7]
Round 2: [4,2,3,1,6,5,7,8][4,2,3,1,6,5,7,8][4,2,3,1,6,5,7,8]
Round 3: [5,3,2,6,4,1,8,7][5,3,2,6,4,1,8,7][5,3,2,6,4,1,8,7]
Round 4: [1,2,3,4,5,6,7,8][1,2,3,4,5,6,7,8][1,2,3,4,5,6,7,8]
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
const int mod = 1e9 + 7;
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
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
const int N = 2e5 + 10;
bitset<N>p;
vector<pair<int , int>>adj[N];
int main() {
    PRE();
 
    p.set();
    p[0] = p[1] = false;
    for (int j = 2;j < N;j++) {
        if (p[j])
        for (int k = j; k < N;k += j) {
            p[k] = false;
            int cnt = 0;
            int temp = k;
            while (temp % j == 0) cnt++ , temp /= j;
            adj[k].emplace_back(j , cnt);
        }
    }
 
    int n;cin >> n;
    dsu d(n);
    for (int i = 0;i < n;i++) {
        int x;cin >> x;x--;
        d.merge(i , x);
    }
    map<int , int> cur;
    for (int i = 0;i < n;i++) {
        if (d.find(i) == i) {
            auto nw = adj[d.size[i]];
            if (nw.empty())continue;
            for (auto &val : nw) {
                cur[val.first] = max(cur[val.first] , val.second);
            }
        }
    }
    ll res = 1;
    for (auto &[v , f] : cur) {
        // cout << v <<" " << f << endl;
        res = res * binpow(v , f , mod) % mod;
    }
    cout << res << '\n';
}