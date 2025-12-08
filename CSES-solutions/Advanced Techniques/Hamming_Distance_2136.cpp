/* problem statement text */
/*
CSES - Hamming Distance

Time limit: 1.00 s
Memory limit: 512 MB

The Hamming distance between two strings aaa and bbb of equal length is the number of positions where the strings differ.
You are given nnn bit strings, each of length kkk and your task is to calculate the minimum Hamming distance between two strings.
Input
The first input line has two integers nnn and kkk: the number of bit strings and their length.
Then there are nnn lines each consisting of one bit string of length kkk.
Output
Print the minimum Hamming distance between two strings.
Constraints

2≤n≤2⋅1042 \le n \le 2 \cdot 10^42≤n≤2⋅104
1≤k≤301 \le k \le 301≤k≤30

Example
Input:
5 6
110111
001000
100001
101000
101110

Output:
1

Explanation: The strings 101000 and 001000 differ only at the first position.
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
    int n, k;
    cin >> n >> k;
    int res = k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (auto &val: s) {
            v[i] <<= 1;
            v[i] |= (val - '0');
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            res = min(res, __builtin_popcount(v[i] ^ v[j]));
        }
    }
    cout << res << '\n';
}