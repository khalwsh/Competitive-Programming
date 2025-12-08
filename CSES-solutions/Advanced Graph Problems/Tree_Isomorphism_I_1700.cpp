/* problem statement text */
/*
CSES - Tree Isomorphism I

Time limit: 1.00 s
Memory limit: 512 MB

Given two rooted trees, your task is to find out if they are isomorphic, i.e., it is possible to draw them so that they look the same.
Input
The first input line has an integer ttt: the number of tests. Then, there are ttt tests described as follows:
The first line has an integer nnn: the number of nodes in both trees. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n, and node 111 is the root.
Then, there are n−1n-1n−1 lines describing the edges of the first tree, and finally n−1n-1n−1 lines describing the edges of the second tree.
Output
For each test, print "YES", if the trees are isomorphic, and "NO" otherwise.
Constraints

1≤t≤10001 \le t \le 10001≤t≤1000
2≤n≤1052 \le n \le 10^52≤n≤105
the sum of all values of nnn is at most 10510^5105

Example
Input:
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2

Output:
NO
YES
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
// Tree Hashing (Subtree Hashing) for a rooted tree
// In case tree in unrooted, you must use "isomorphism.cpp"
// Time Complexity: O(n log n)
//
// This function computes a hash for each subtree in a rooted tree.
// It can be used to test subtree isomorphism. Optionally, sort children
// before hashing to ignore child order (unordered rooted tree).
 
map<vector<int>, int> mp;
 
int tree_hash(int u, int p, vector<int> adj[]) {
    vector<int> child;
    for (auto &v : adj[u]) {
        if (v != p) {
            child.emplace_back(tree_hash(v, u, adj));
        }
    }
    sort(child.begin() , child.end());
    if (!mp.count(child)) {
        mp[child] = mp.size() + 1;
    }
    return mp[child];
}
int main() {
    PRE();
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        vector<int> adj1[n] , adj2[n];
        mp.clear();
        for (int i = 0;i < n - 1;i++) {
            int u , v;cin >> u >> v;
            u-- , v--;
            adj1[u].emplace_back(v);
            swap(u , v);
            adj1[u].emplace_back(v);
        }
        for (int i = 0;i < n - 1;i++) {
            int u , v;cin >> u >> v;
            u-- , v--;
            adj2[u].emplace_back(v);
            swap(u , v);
            adj2[u].emplace_back(v);
        }
        if (tree_hash(0 , -1 , adj1) == tree_hash(0 , -1 , adj2)) cout << "YES";
        else cout << "NO";
        cout << '\n';
    }
}