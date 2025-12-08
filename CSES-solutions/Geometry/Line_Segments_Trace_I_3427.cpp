/* problem statement text */
/*
CSES - Line Segments Trace I

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn line segments whose endpoints have integer coordinates. The left x-coordinate of each segment is 000 and the right x-coordinate is mmm. The slope of each segment is an integer.
For each x-coordinate 0,1,…,m0,1,\dots,m0,1,…,m, find the maximum point in any line segment.
Input
The first line has two integers nnn and mmm: the number of line segments and the maximum x-coordinate.
The next nnn lines describe the line segments. Each line has two integers y1y_1y1​ and y2y_2y2​: there is a line segment between points (0,y1)(0,y_1)(0,y1​) and (m,y2)(m,y_2)(m,y2​).
Output
Print m+1m+1m+1 integers: the maximum points for x=0,1,…,mx=0,1,\dots,mx=0,1,…,m.
Constraints

1≤n,m≤1051 \le n, m \le 10^51≤n,m≤105
0≤y1,y2≤1090 \le y_1,y_2 \le 10^90≤y1​,y2​≤109

Example
Input:
4 5
1 6
7 2
5 5
10 0

Output:
10 8 6 5 5 6
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const ll DEFAULT = LLONG_MIN;
const int N = 1e9+9;
 
struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {}
    ll operator()(ll x) const { return m * x + c; }
};
 
struct Node {
    Line line;
    Node *left = nullptr, *right = nullptr;
    Node(Line line = Line()) : line(line) {}
};
 
void insert(Line newLine, Node*& root, ll l = -N, ll r = N) {
    if (!root) {
        root = new Node(newLine);
        return;
    }
 
    ll m = (l + r) / 2;
    // (<) -> min f(x) , (>) -> max f(x)
    bool lef = newLine(l) > root->line(l);
    bool mid = newLine(m) > root->line(m);
 
    if (mid)
        swap(root->line, newLine);
 
    if (r - l == 1)
        return;
 
    if (lef != mid)
        insert(newLine, root->left, l, m);
    else
        insert(newLine, root->right, m, r);
}
 
ll query(ll x, Node* cur, ll l = -N, ll r = N) {
    if (!cur)
        return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return cur->line(x);
    if (x < m)
        return max(cur->line(x), query(x, cur->left, l, m));
    else
        return max(cur->line(x), query(x, cur->right, m, r));
}
int main() {
    PRE();
    int n , m;cin >> n >> m;
    Node*root = nullptr;
    for (int i = 0;i < n;i++) {
        int y1 , y2;cin >> y1 >> y2;
        //(0 , y1) ---> (m , y2)
        insert({((y2 - y1)) / (m) , y1}  , root);
    }
    for (int i = 0;i <= m;i++) cout << query(i , root) << ' ';
}