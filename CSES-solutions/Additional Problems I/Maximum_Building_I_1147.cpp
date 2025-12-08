/* problem statement text */
/*
CSES - Maximum Building I

Time limit: 1.00 s
Memory limit: 512 MB

You are given a map of a forest where some squares are empty and some squares have trees.
What is the maximum area of a rectangular building that can be placed in the forest so that no trees must be cut down?
Input
The first input line contains integers nnn and mmm: the size of the forest.
After this, the forest is described. Each square is empty (.) or has trees (*).
Input
Print the maximum area of a rectangular building.
Constraints

1≤n,m≤10001 \le n,m \le 10001≤n,m≤1000

Example
Input:
4 7
...*.*.
.*.....
.......
......*

Output:
12
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
int zero_matrix(vector<vector<int>> a) {
    int n = a.size();
    int m = a[0].size();
 
    int ans = 0;
    vector<int> d(m, -1), d1(m), d2(m);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1)
                d[j] = i;
        }
 
        for (int j = 0; j < m; ++j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d1[j] = st.empty() ? -1 : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();
 
        for (int j = m - 1; j >= 0; --j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d2[j] = st.empty() ? m : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();
 
        for (int j = 0; j < m; ++j)
            ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1));
    }
    return ans;
}
int main() {
    PRE();
    int n , m; cin >> n >> m;
    vector<vector<int>> v(n , vector<int>(m));
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            char ch;cin >> ch;
            v[i][j] = (ch == '*');
        }
    }
    cout << zero_matrix(v);
}