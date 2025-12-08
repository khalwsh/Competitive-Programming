/* problem statement text */
/*
CSES - Visible Buildings Queries

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn buildings in a row numbered 1,2,…,n1, 2,\dots, n1,2,…,n from left to right. You are standing to the left of the first building. You can see a building if it is taller than all buildings to its left.
Your task is to process qqq queries: If only buildings in range [a,b][a, b][a,b] existed, how many buildings would you see?
Input
The first line has two integers nnn and qqq: the number of buildings and queries.
The second line has nnn integers h1,h2,…,hnh_1, h_2, \dots, h_nh1​,h2​,…,hn​: the heights of the buildings.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb.
Output
For each query, print one integer: the number of visible buildings.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤q≤2⋅1051 \le q \le 2 \cdot 10^51≤q≤2⋅105
1≤hi≤1091 \le h_i \le 10^91≤hi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 3
4 1 2 2 3
1 5
2 5
3 4

Output:
1
3
1
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
 
template<class T>
struct Fenwick{
    int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
    int n;
    vector<T>tree;
    int N = 1;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
        N = log2_floor(n) + 1;
    }
    void add(int pos,T value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    T get(int pos) {
        T sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    T query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
    int lower_bound(T t){
        T sum = 0;
        int pos = 0;
        for(int i = N; i >= 0; i--){
            int next_pos = pos + (1 << i);
            if(next_pos <= n && sum + tree[next_pos - 1] < t){
                sum += tree[next_pos - 1];
                pos = next_pos;
            }
        }
        return pos; // zero-based index
    }
};
 
int main() {
    PRE();
    int n , q;cin >> n >> q;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    vector<pair<int , int>>queries[n];
    for (int i = 0;i < q;i++) {
        int l , r;cin >> l >> r;
        l-- , r--;
        queries[l].emplace_back(r , i);
    }
    Fenwick<ll> fen;
    fen.init(n);
    vector<int>ans(q);
    set<pair<int ,int>>exist;
    for (int i = n - 1;i >= 0;i--) {
        auto it = exist.upper_bound({v[i] , 1e9});
        for (auto nxt = exist.begin(); nxt != it;nxt++) {
            auto [val , idx] = *nxt;
            fen.add(idx , -1);
        }
        fen.add(i , 1);
        exist.erase(exist.begin() , it);
        exist.insert({v[i] , i});
        for (auto &[r , idx] : queries[i]) {
            ans[idx] = fen.query(i , r);
        }
    }
    for (int i = 0;i < q;i++) cout << ans[i] << "\n";
}