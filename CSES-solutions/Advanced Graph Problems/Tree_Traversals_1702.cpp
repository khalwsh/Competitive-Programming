/* problem statement text */
/*
CSES - Tree Traversals

Time limit: 1.00 s
Memory limit: 512 MB

There are three common ways to traverse the nodes of a binary tree:

Preorder: First process the root, then the left subtree, and finally the right subtree.
Inorder: First process the left subtree, then the root, and finally the right subtree.
Postorder: First process the left subtree, then the right subtree, and finally the root.

There is a binary tree of nnn nodes with distinct labels. You are given the preorder and inorder traversals of the tree, and your task is to determine its postorder traversal.
Input
The first input line has an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are two lines describing the preorder and inorder traversals of the tree. Both lines consist of nnn integers.
You can assume that the input corresponds to a binary tree.
Output
Print the postorder traversal of the tree.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105

Example
Input:
5
5 3 2 1 4
3 5 1 2 4

Output:
3 1 4 2 5
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
const int N = 2e5 + 1;
int p[N], I[N], pos[N];
int n;
bool found = true;
pair<int, int> child[N];
 
int j = 0;
 
int solve(int L, int R) {
    if (L > R) return 0;
    int node = p[j];
    j++;
    int Pos = pos[node];
    if (Pos < L || Pos > R) {
        cout << -1 << '\n';
        exit(0);
    }
    if (L == R) return node;
    child[node].first = solve(L, Pos - 1);
    child[node].second = solve(Pos + 1, R);
    return node;
}
void solve2(int u) {
    if (child[u].first != 0) solve2(child[u].first);
    if (child[u].second != 0) solve2(child[u].second);
    cout << u << " ";
}
int main() {
    PRE();
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> I[i], pos[I[i]] = i;
    int root = solve(0, n - 1);
    solve2(root);
}