/* problem statement text */
/*
CSES - Graph Paths II

Time limit: 1.00 s
Memory limit: 512 MB

Consider a directed weighted graph having nnn nodes and mmm edges. Your task is to calculate the minimum path length from node 111 to node nnn with exactly kkk edges.
Input
The first input line contains three integers nnn, mmm and kkk: the number of nodes and edges, and the length of the path. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are m lines describing the edges. Each line contains three integers aaa, bbb and ccc: there is an edge from node aaa to node bbb with weight ccc.
Output
Print the minimum path length. If there are no such paths, print −1-1−1.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤m≤n(n−1)1 \le m \le n(n-1)1≤m≤n(n−1)
1≤k≤1091 \le k \le 10^91≤k≤109
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
3 4 8
1 2 5
2 3 4
3 1 1
3 2 2

Output:
27
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
template<class T>
struct Matrix {
    vector<vector<T>>v;
    int n , m;
    Matrix(int n , int m , ll def): n(n) , m(m) , v(vector<vector<T>>(n , vector<T>(m , def))){}
    Matrix<T> operator*(const Matrix<T>&other) {
        assert(m == other.n);
        Matrix<T>res(n , other.m , 2e18 + 1);
        for(int i = 0;i < n;i++) {
            for(int k = 0;k < m;k++) {
                // if(v[i][k] == 0)continue;
                for(int j = 0;j < other.m;j++) {
                    res.v[i][j] = min(res.v[i][j] , v[i][k] + other.v[k][j]);
                }
            }
        }
        return res;
    }
    Matrix<T> power(ll k) {
        assert(n == m);
        Matrix<T>res(n , m , 2e18 + 1);
        Matrix a = *this;
        for(int i = 0;i < n;i++)res.v[i][i] = 0;
        while(k > 0) {
            if(k & 1) {
                res = res * a;
            }
            a = a * a;
            k >>=1;
        }
        return res;
    }
 
    Matrix<T> operator+(const Matrix<T> &b){
        assert(n == b.n && m == b.m);
        Matrix<T> res(b.n , b.m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.v[i][j] = v[i][j] + b.v[i][j];
            }
        }
        return res;
    }
 
    Matrix<T> Identity(int n , int m) {
        assert(n == m);
        Matrix<T> res(n ,m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.v[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            res.v[i][i] = 1;
        }
        return res;
    }
 
    Matrix<T> Spower(ll k) {
        if(k == 0)return Matrix(n , m);
        if (k & 1) {
            return *this * (Identity(n , m) + Spower(k - 1));
        }
        return Spower(k / 2) * (Identity(n , m) + power(k / 2));
    }
};
int main() {
    PRE();
    int n , m;
    ll k; cin >> n >> m >> k;
    Matrix<ll> g(n , n , 2e18 + 2);
    // cout << g.v[0][n - 1] << endl;
    for (int i = 0;i < m;i++) {
        ll u , v , w;cin >> u >> v >> w;
        u-- , v--;
        g.v[u][v] = min(w , g.v[u][v]);
    }
    auto res = (g.power(k)).v[0][n - 1];
    if (res <= 1e18) cout << res;
    else cout << -1;
}