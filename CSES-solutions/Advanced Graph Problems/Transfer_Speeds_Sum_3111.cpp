/* problem statement text */
/*
CSES - Transfer Speeds Sum

Time limit: 1.00 s
Memory limit: 512 MB

A computer network has nnn computers and n−1n-1n−1 connections between two computers. Information can be exchanged between every pair of computers using the connections.
Each connection has a certain transfer speed. Let d(a,b)d(a,b)d(a,b) denote the transfer speed between computers aaa and bbb, which is the speed of the slowest connection on the route between aaa and bbb. Your task is to compute the sum of transfer speeds between all pairs of computers.
Input
The first line contains the integer nnn: the number of computers. The computers are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are n−1n-1n−1 lines, which describe the connections. Each line has three integers aaa, bbb and xxx: there is a connection between computers aaa and bbb with transfer speed xxx.
Output
Print one integer: the sum of transfer speeds.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤x≤1061 \le x \le 10^61≤x≤106

Example
Input:
4
1 2 5
2 3 1
2 4 2

Output:
12

Explanation: The following figure corresponds to the sample input:

Here d(1,2)=5d(1,2)=5d(1,2)=5, d(1,3)=1d(1,3)=1d(1,3)=1, d(1,4)=2d(1,4)=2d(1,4)=2, d(2,3)=1d(2,3)=1d(2,3)=1, d(2,4)=2d(2,4)=2d(2,4)=2, and d(3,4)=1d(3,4)=1d(3,4)=1, so the sum of transfer speeds is 121212.
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
struct dsu {
    vector<int> p , s;
    dsu(int n) {
        p.resize(n);
        s.resize(n , 1);
        iota(p.begin() , p.end() , 0);
    }
    int find(int ch) {
        return (ch == p[ch] ? ch : p[ch] = find(p[ch]));
    }
    void merge(int a , int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] < s[b]) swap(a , b);
        s[a] += s[b];
        p[b] = a;
    }
};
int main() {
    PRE();
    int n; cin >> n;
    dsu d(n);
    vector<array<int , 3>> e(n - 1);
    for (auto &[u , v , w] : e) cin >> u >> v >> w , u-- , v--;
    ll res = 0;
    sort(e.begin() , e.end() , [&](array<int , 3> &a , array<int , 3>&b) -> bool {
        return a[2] > b[2];
    });
    for (auto &[u , v , w] : e) {
        if (d.find(u) != d.find(v)) res += 1LL * w * d.s[d.find(u)] * d.s[d.find(v)] , d.merge(u , v);
    }
    cout << res << '\n';
}