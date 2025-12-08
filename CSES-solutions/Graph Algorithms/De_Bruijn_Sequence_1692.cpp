/* problem statement text */
/*
CSES - De Bruijn Sequence

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to construct a minimum-length bit string that contains all possible substrings of length nnn. For example, when n=2n=2n=2, the string 00110 is a valid solution, because its substrings of length 222 are 00, 01, 10 and 11.
Input
The only input line has an integer nnn.
Output
Print a minimum-length bit string that contains all substrings of length nnn. You can print any valid solution.
Constraints

1≤n≤151 \le n \le 151≤n≤15

Example
Input:
2

Output:
00110
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
 
int main() {
    PRE();
    int n;
    cin >> n;
    if (n == 1) {
        cout << "10" << '\n';
        return 0;
    }
 
    vector<vector<int>> adj(1 << (n - 1));
    for (int node = 0; node < (1 << (n - 1)); node++) {
        int son = (node << 1) % (1 << (n - 1));
        adj[node].push_back(son);
        adj[node].push_back(son | 1);
    }
 
    stack<int> todo;
    todo.push(0);
    vector<int> path;
    while (!todo.empty()) {
        int node = todo.top();
        if (!adj[node].empty()) {
            todo.push(adj[node].back());
            adj[node].pop_back();
        } else {
            path.push_back(node & 1);
            todo.pop();
        }
    }
    for (int i = 0; i < n - 2; i++) { path.push_back(0); }
 
    for (int digit : path) { cout << digit; }
    cout << '\n';
}