/* problem statement text */
/*
CSES - Sliding Window Minimum

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the minimum of each window of kkk elements, from left to right.
In this problem the input data is large and it is created using a generator.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
The next line contains four integers xxx, aaa, bbb and ccc: the input generator parameters. The input is generated as follows:

x1=xx_1=xx1​=x
xi=(axi−1+b) mod cx_i=(ax_{i-1}+b) \bmod cxi​=(axi−1​+b)modc for i=2,3,…,ni=2,3,\dots,ni=2,3,…,n

Output
Print the xor of all window minimums.
Constraints

1≤k≤n≤1071 \le k \le n \le 10^71≤k≤n≤107
0≤x,a,b≤1090 \le x, a, b \le 10^90≤x,a,b≤109
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
8 5
3 7 1 11

Output:
3

Explanation: The input array is [3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6]. The windows are [3,0,1,8,2][3,0,1,8,2][3,0,1,8,2], [0,1,8,2,4][0,1,8,2,4][0,1,8,2,4], [1,8,2,4,7][1,8,2,4,7][1,8,2,4,7] and [8,2,4,7,6][8,2,4,7,6][8,2,4,7,6], and their minimums are 000, 000, 111 and 222. Thus, the answer is 0⊕0⊕1⊕2=30 \oplus 0 \oplus 1 \oplus 2 = 30⊕0⊕1⊕2=3.
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
// Monotonic deque for sliding-window minimum
const ll POS_INF = 1e18;
struct DequeMin {
    deque<pair<int, ll>> dq;
    void push(int idx, ll val) {
        while (!dq.empty() && dq.back().second >= val)
            dq.pop_back();
        dq.emplace_back(idx, val);
    }
    ll getMin(int l) {
        while (!dq.empty() && dq.front().first < l)
            dq.pop_front();
        return dq.empty() ? POS_INF : dq.front().second;
    }
    void clear() { dq.clear(); }
};
int main() {
    PRE();
    int n , k;
    ll x , a , b , c;
    cin >> n >> k >> x >> a >> b >> c;
    ll ans = 0;
    vector<ll>v(n);
    v[0] = x;
    for (int i = 1;i < n;i++) {
        v[i] = (v[i - 1] * a + b) % c;
    }
    DequeMin dq;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            ans ^= dq.getMin(i - k);
        }
        dq.push(i , v[i]);
    }
    ans ^= dq.getMin(n - k);
    cout << ans << '\n';
}