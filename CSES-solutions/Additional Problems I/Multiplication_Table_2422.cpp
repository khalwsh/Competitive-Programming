/* problem statement text */
/*
CSES - Multiplication Table

Time limit: 1.00 s
Memory limit: 512 MB

Find the middle element when the numbers in an n×nn \times nn×n multiplication table are sorted in increasing order. It is assumed that nnn is odd.
For example, the 3×33 \times 33×3 multiplication table is as follows:
123246369
\begin{matrix}
1 & 2 & 3 \\
2 & 4 & 6 \\
3 & 6 & 9 \\
\end{matrix}
123​246​369​
The numbers in increasing order are [1,2,2,3,3,4,6,6,9][1,2,2,3,3,4,6,6,9][1,2,2,3,3,4,6,6,9], so the answer is 333.
Input
The only input line has an integer nnn.
Output
Print one integer: the answer to the task.
Constraints

1≤n<1061 \le n < 10^61≤n<106

Example
Input:
3

Output:
3
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
    ll n; cin >> n;
    ll left = 1 , right = n * n;
    ll res = 1;
    auto can = [&](ll mid) -> bool {
        ll tar = (n * n) / 2 + 1;
        ll cnt = 0;
        for (int i = 1;i <= n;i++) {
            cnt += min(n , mid / i);
        }
        return cnt >= tar;
    };
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (can(mid)) {
            right = mid - 1;
            res = mid;
        }else
            left = mid + 1;
    }
    cout << res << '\n';
}