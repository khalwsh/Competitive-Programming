#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
struct dsu {
    vector<int>size , parent;
    int cnt = 0;
    stack<array<int , 5>>sk;
    dsu(int n) {
        size.resize(n , 1);
        cnt = n;
        parent.resize(n , 0);
        iota(parent.begin() , parent.end() , 0);
    }
    int find(int child) {
        return (child == parent[child]) ? child : find(parent[child]);
    }
    bool merge(int a , int b) {
        a = find(a) ,b = find(b);

        if(a == b) {
            sk.push(array<int , 5>{-1 , -1 , -1 , -1 , -1});
            return false;
        }
        if(size[a] > size[b])swap(a , b);
        // size[b] ? , parent[a] ? , cnt ?
        sk.push(array<int , 5>{a , b , size[b] , parent[a] , cnt});
        cnt--;
        size[b] += size[a];
        parent[a] = b;
        return true;
    }
    void rollback(int x) {
        while(x-- && sk.size()) {
            auto [a , b , sb , pa , oldcnt] = sk.top();
            sk.pop();
            if(oldcnt == -1)continue;
            size[b] = sb;
            parent[a] = pa;
            cnt = oldcnt;
        }
    }
};
struct Query {
    int l , r , id;
};

const int N = 300001;
int n , m , q;
pair<int , int>edges[N];
int ans[N];
int BLOCKSIZE = 0;
vector<Query> Buckets[500];
int main() {
    PRE();
    int t;cin>>t;
    while(t--) {
        cin>>n>>m>>q;
        for(int i = 0;i < m;i++) {
            cin>>edges[i].first>>edges[i].second;
            edges[i].first-- , edges[i].second--;
        }
        BLOCKSIZE = sqrt(n) + 2;
        int tot = (m + BLOCKSIZE - 1) / BLOCKSIZE;
        for(int i = 0;i < tot;i++)Buckets[i].clear();
        for(int i = 0;i < q;i++) {
            int l , r;cin>>l>>r;
            l-- ,r--;
            Buckets[l / BLOCKSIZE].emplace_back(l ,r ,  i);
        }
        for(int i = 0;i < tot;i++) {
            sort(Buckets[i].begin() , Buckets[i].end() , [&](const Query &a , const Query &b)->bool {
                return a.r < b.r;
            });
            dsu d(n);
            int base = (i + 1) * BLOCKSIZE;
            int r = base;
            for(auto &qu : Buckets[i]) {
                while(r <= qu.r) {
                    d.merge(edges[r].first , edges[r].second);
                    r++;
                }
                int temp = 0;
                while(qu.l <= min(base - 1, qu.r)) {
                    d.merge(edges[qu.l].first , edges[qu.l].second);
                    qu.l++;
                    temp++;
                }
                ans[qu.id] = d.cnt;
                d.rollback(temp);
            }
        }
        for(int i = 0;i < q;i++)
            cout<<ans[i]<<'\n';
    }
}
