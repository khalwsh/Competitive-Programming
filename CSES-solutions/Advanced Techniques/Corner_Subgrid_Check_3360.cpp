/* problem statement text */
/*
CSES - Corner Subgrid Check

Time limit: 1.00 s
Memory limit: 512 MB

You are given a grid of letters. Your task is to find subgrids whose height and width is at least two and all the corners have the same letter.
For each letter, check if there is a valid subgrid whose corners have that letter.
Input
The first line has two integers nnn and kkk: the size of the grid and the number of letters. The letters are the first kkk uppercase letters.
After this, there are nnn lines that describe the grid. Each line has nnn letters.
Output
Print kkk lines: for each letter, YES if there is a valid subgrid and NO otherwise.
Constraints

1≤n≤30001 \le n \le 30001≤n≤3000
1≤k≤261 \le k \le 261≤k≤26

Example
Input:
4 5
AAAA
CBBC
CBBE
AAAA

Output:
YES
YES
NO
NO
NO
*/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("popcnt")
 
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
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i] = s;
    }
    for (int ch = 0; ch < m; ch++) {
        vector<bitset<3000> > bs(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bs[i][j] = (v[i][j] - 'A') == ch;
            }
        }
        bool ok = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((bs[i] & bs[j]).count() >= 2) {
                    ok = true;
                    break;
                }
            }
            if (ok)break;
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}