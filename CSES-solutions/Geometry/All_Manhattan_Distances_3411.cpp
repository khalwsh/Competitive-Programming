/* problem statement text */
/*
CSES - All Manhattan Distances

Time limit: 1.00 s
Memory limit: 512 MB

Given a set of points, calculate the sum of all Manhattan distances between two point pairs.
Input
The first line has an integer nnn: the number of points.
The following nnn lines describe the points. Each line has two integers xxx and yyy. You can assume that each point is distinct.
Output
Print the sum of all Manhattan distances.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤x,y≤109-10^9 \le x, y \le 10^9−109≤x,y≤109

Example
Input:
5
1 1
3 2
2 4
2 1
4 5

Output:
36
*/
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
    freopen("out.txt", "w",stdout);
    freopen("error.txt", "w",stderr);
#endif
}
 
i128 solve(const vector<int> &v) {
    vector<int> a = v;
    sort(a.begin(), a.end());
    i128 cnt = 0, res = 0, sum = 0;
    int n = (int) a.size();
    for (int i = 0; i < n; ++i) {
        // use i128 casts to avoid 64-bit intermediate overflow
        res += (i128) a[i] * cnt - sum;
        sum += (i128) a[i];
        ++cnt;
    }
    return res;
}
 
void print_i128(i128 x) {
    if (x == 0) {
        cout << '0';
        return;
    }
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    string s;
    while (x > 0) {
        int d = int(x % 10);
        s.push_back(char('0' + d));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    cout << s;
}
 
int main() {
    PRE();
    int n;
    if (!(cin >> n)) return 0;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
 
    i128 ans = solve(x) + solve(y); // unordered pairs sum of Manhattan distances
    // If problem expects ordered pairs (count both directions), multiply by 2:
    // ans *= 2;
 
    print_i128(ans);
    cout << '\n';
    return 0;
}