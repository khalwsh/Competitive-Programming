/* problem statement text */
/*
CSES - Prüfer Code

Time limit: 1.00 s
Memory limit: 512 MB

A Prüfer code of a tree of nnn nodes is a sequence of n−2n-2n−2 integers that uniquely specifies the structure of the tree.
The code is constructed as follows: As long as there are at least three nodes left, find a leaf with the smallest label, add the label of its only neighbor to the code, and remove the leaf from the tree.
Given a Prüfer code of a tree, your task is to construct the original tree.
Input
The first input line contains an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
The second line contains n−2n-2n−2 integers: the Prüfer code.
Output
Print n−1n-1n−1 lines describing the edges of the tree. Each line has to contain two integers aaa and bbb: there is an edge between nodes aaa and bbb. You can print the edges in any order.
Constraints

3≤n≤2⋅1053 \le n \le 2 \cdot 10^53≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5
2 2 4

Output:
1 2
2 3
2 4
4 5
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
vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
    int n = code.size() + 2;
    vector<int> degree(n, 1);
    for (int i : code)
        degree[i]++;
 
    int ptr = 0;
    while (degree[ptr] != 1)
        ptr++;
    int leaf = ptr;
 
    vector<pair<int, int>> edges;
    for (int v : code) {
        edges.emplace_back(leaf, v);
        if (--degree[v] == 1 && v < ptr) {
            leaf = v;
        } else {
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n-1);
    return edges;
}
int main() {
    PRE();
    int n;cin >> n;
    vector<int> code(n - 2);
    for (auto &val : code) cin >> val , val -= 1;
    for (auto &val : pruefer_decode(code)) cout << val.first + 1 << " " << val.second + 1 << '\n';
}