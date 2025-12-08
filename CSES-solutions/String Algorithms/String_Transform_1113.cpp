/* problem statement text */
/*
CSES - String Transform

Time limit: 1.00 s
Memory limit: 512 MB

Consider the following string transformation:

append the character # to the string (we assume that # is lexicographically smaller than all other characters of the string)
generate all rotations of the string
sort the rotations in increasing order
based on this order, construct a new string that contains the last character of each rotation

For example, the string babc becomes babc#. Then, the sorted list of rotations is #babc, abc#b, babc#, bc#ba, and c#bab. This yields a string cb#ab.
Input
The only input line contains the transformed string of length n+1n+1n+1. Each character of the original string is one of a–z.
Output
Print the original string of length nnn.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
cb#ab

Output:
babc
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(std::ios::fixed);
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    freopen("error.txt","w",stderr);
#endif
}
static int charId(char c) {
    return (c == '#') ? 0 : (c - 'a') + 1;
}
 
string build(const string &L) {
    int m = (int)L.size();
    if (m == 0) return {};
    if (m == 1) return {};
 
    vector<vector<int>> pos(27);
    pos.reserve(27);
    for (int i = 0; i < m; ++i) pos[charId(L[i])].push_back(i);
 
    vector<int> nxt(m);
    int idx = 0;
    for (int c = 0; c < 27; ++c) {
        for (int p : pos[c]) {
            nxt[idx++] = p;
        }
    }
 
    int p = nxt[0];
    string res;
 
    for (int i = 0; i < m - 1; ++i) {
        p = nxt[p];
        res.push_back(L[p]);
    }
    return res;
}
int main() {
    PRE();
    string s;cin >> s;
    cout << build(s) << '\n';
}