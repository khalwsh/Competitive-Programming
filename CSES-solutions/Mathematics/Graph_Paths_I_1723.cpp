/* problem statement text */
/*
CSES - Graph Paths I

Time limit: 1.00 s
Memory limit: 512 MB

Consider a directed graph that has nnn nodes and mmm edges. Your task is to count the number of paths from node 111 to node nnn with exactly kkk edges.
Input
The first input line contains three integers nnn, mmm and kkk: the number of nodes and edges, and the length of the path. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the edges. Each line contains two integers aaa and bbb: there is an edge from node aaa to node bbb.
Output
Print the number of paths modulo 109+710^9+7109+7.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤m≤n(n−1)1 \le m \le n(n-1)1≤m≤n(n−1)
1≤k≤1091 \le k \le 10^91≤k≤109
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
3 4 8
1 2
2 3
3 1
3 2

Output:
2

Explanation: The paths are 1→2→3→1→2→3→1→2→31 \rightarrow 2 \rightarrow 3 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 1 \rightarrow 2 \rightarrow 31→2→3→1→2→3→1→2→3 and 1→2→3→2→3→2→3→2→31 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 31→2→3→2→3→2→3→2→3.
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
    Matrix(int n , int m): n(n) , m(m) , v(vector<vector<T>>(n , vector<T>(m , 0))){}
    Matrix<T> operator*(const Matrix<T>&other) {
        assert(m == other.n);
        Matrix<T>res(n , other.m);
        for(int i = 0;i < n;i++) {
            for(int k = 0;k < m;k++) {
                if(v[i][k] == 0)continue;
                for(int j = 0;j < other.m;j++) {
                    res.v[i][j] += v[i][k] * other.v[k][j];
                    res.v[i][j] %= mod;
                }
            }
        }
        return res;
    }
    Matrix<T> power(ll k) {
        assert(n == m);
        Matrix<T>res(n , m);
        Matrix a = *this;
        for(int i = 0;i < n;i++)res.v[i][i] = 1;
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
    Matrix<ll> g(n , n);
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        g.v[u][v] += 1;
    }
    cout << (g.power(k)).v[0][n - 1];
}