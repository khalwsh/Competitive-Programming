/* problem statement text */
/*
CSES - Sum of Four Squares

Time limit: 1.00 s
Memory limit: 512 MB

A well known result in number theory is that every non-negative integer can be represented as the sum of four squares of non-negative integers.
You are given a non-negative integer nnn. Your task is to find four non-negative integers aaa, bbb, ccc and ddd such that n=a2+b2+c2+d2n = a^2 + b^2 + c^2 + d^2n=a2+b2+c2+d2.
Input
The first line has an integer ttt: the number of test cases.
Each of the next ttt lines has an integer nnn.
Output
For each test case, print four non-negative integers aaa, bbb, ccc and ddd that satisfy n=a2+b2+c2+d2n = a^2 + b^2 + c^2 + d^2n=a2+b2+c2+d2.
Constraints

1≤t≤10001 \le t \le 10001≤t≤1000
0≤n≤1070 \le n \le 10^70≤n≤107
the sum of all nnn is at most 10710^7107

Example
Input:
3
5
30
322266

Output:
2 1 0 0
1 2 3 4
314 159 265 358
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
const int N = 1e7 + 10;
bool is_pref[N];
int main(){
    PRE();
    for (int i = 0;i * i < N;i++) {
        is_pref[i * i] = true;
    }
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        for (int i = 0;i * i <= n;i++) {
            for (int j = i;j * j + i * i <= n;j++) {
                for (int k = j;k * k + j * j + i * i <= n;k++) {
                    if (is_pref[n - k * k - j * j - i * i]) {
                        cout << i << " " << j << " " << k << " " << sqrt(n - k * k - j * j - i * i) << '\n';
                        goto done;
                    }
                }
            }
        }
        done : ;
    }
}