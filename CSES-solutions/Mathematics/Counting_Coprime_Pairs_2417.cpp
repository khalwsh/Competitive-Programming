/* problem statement text */
/*
CSES - Counting Coprime Pairs

Time limit: 1.00 s
Memory limit: 512 MB

Given a list of nnn positive integers, your task is to count the number of pairs of integers that are coprime (i.e., their greatest common divisor is one).
Input
The first input line has an integer nnn: the number of elements.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the list.
Output
Print one integer: the answer for the task.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤xi≤1061 \le x_i \le 10^61≤xi​≤106

Example
Input:
8
5 4 20 1 16 17 5 15

Output:
19
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
const int N = 1e6 + 10;
int freq[N], cnt[N];
ll dp[N];
int main() {
    PRE();
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            cnt[i] += freq[j];
        }
    }
    for (int i = N - 1; i > 0; i--) {
        ll total = 1LL * cnt[i] * (cnt[i] - 1) / 2;
        for (int j = 2 * i; j < N; j += i) {
            total -= dp[j];
        }
        dp[i] = total;
    }
 
    cout << dp[1] << "\n";
}