/* problem statement text */
/*
CSES - Sliding Window Inversions

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the number of inversions in each window of kkk elements, from left to right.
An inversion is a pair of elements where the left element is larger than the right element.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print n−k+1n-k+1n−k+1 values: the numbers of inversions.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
1 2 3 2 5 2 4 4

Output:
0 1 1 1 2 0
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
    int n;cin >> n;
    int k;cin >> k;
    vector<int>v(n) , all;
    for (int i = 0;i < n;i++) {
        cin >> v[i];
        all.emplace_back(v[i]);
    }
    all.emplace_back(0);
    sort(all.begin() , all.end());
    all.erase(unique(all.begin() ,  all.end()) , all.end());
    for (int i = 0;i < n;i++) {
        v[i] = lower_bound(all.begin() , all.end() , v[i]) - all.begin();
    }
    Fenwick<ll> fen;
    fen.init(n + 10);
    ll ans = 0;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            cout << ans << " ";
            ans -= fen.query(0 , v[i - k] - 1);
            fen.add(v[i - k] , -1);
        }
        ans += fen.query(v[i] + 1 , n + 9);
        fen.add(v[i] , 1);
    }
    cout << ans ;
}