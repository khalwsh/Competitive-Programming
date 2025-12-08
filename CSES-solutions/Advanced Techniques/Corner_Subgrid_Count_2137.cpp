/* problem statement text */
/*
CSES - Corner Subgrid Count

Time limit: 1.00 s
Memory limit: 512 MB

You are given an n×nn \times nn×n grid whose each square is either black or white. A subgrid is called beautiful if its height and width is at least two and all of its corners are black. How many beautiful subgrids are there within the given grid?
Input
The first input line has an integer nnn: the size of the grid.
Then there are nnn lines describing the grid: 1 means that a square is black and 0 means it is white.
Output
Print the number of beautiful subgrids.
Constraints

1≤n≤30001 \le n \le 30001≤n≤3000

Example
Input:
5
00010
11111
00110
11001
00010

Output:
4
*/
#include <bits/stdc++.h>
using namespace std;
#define static_assert(...);
#include <tr2/dynamic_bitset>
using custom_bitset = tr2::dynamic_bitset<long long>;
#pragma GCC target("popcnt")
 
// custom_bitset(10)
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
 
const int N = 3001;
custom_bitset arr[N];
 
int main() {
    PRE();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr[i] = custom_bitset(s);
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = (arr[i] & arr[j]).count();
            res += 1LL * x * (x - 1) / 2;
        }
    }
    cout << res << '\n';
}