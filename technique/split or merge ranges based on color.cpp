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
const int N = 5e5 + 10;
int cur[N];
int main() {
    PRE();
    int n , q;cin >> n >> q;
    set<pair<int,int>> b;
    while(q--){
        int x; cin>>x;
        if(!cur[x]){
            auto it = b.upper_bound({x, 1000000000});
            bool lad=false, rad=false;
            auto lit = it;
            if(it!=b.begin()){
                lit = prev(it);
                if(lit->second==x-1) lad=true;
            }
            if(it!=b.end() && it->first==x+1) rad=true;
            if(lad && rad){
                int L = lit->first, R = lit->second;
                int L2 = it->first, R2 = it->second;
                b.erase(lit);
                b.erase(it);
                b.insert({L,R2});
            } else if(lad){
                int L = lit->first, R = lit->second;
                b.erase(lit);
                b.insert({L,R+1});
            } else if(rad){
                int L2 = it->first, R2 = it->second;
                b.erase(it);
                b.insert({x,R2});
            } else {
                b.insert({x,x});
            }
            cur[x]=1;
        } else {
            auto it = b.upper_bound({x, 1000000000});
            it = prev(it);
            int L = it->first, R = it->second;
            b.erase(it);
            if(L<x && x<R){
                b.insert({L,x-1});
                b.insert({x+1,R});
            } else if(L==x && R==x){
            } else if(L==x){
                b.insert({L+1,R});
            } else if(R==x){
                b.insert({L,R-1});
            }
            cur[x]=0;
        }
        cout << (int)b.size() << '\n';
    }
}
