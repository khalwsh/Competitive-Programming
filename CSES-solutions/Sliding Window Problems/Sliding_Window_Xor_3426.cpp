/* problem statement text */
/*
CSES - Sliding Window Xor

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the bitwise xor of each window of kkk elements, from left to right.
In this problem the input data is large and it is created using a generator.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
The next line contains four integers xxx, aaa, bbb and ccc: the input generator parameters. The input is generated as follows:

x1=xx_1=xx1​=x
xi=(axi−1+b) mod cx_i=(ax_{i-1}+b) \bmod cxi​=(axi−1​+b)modc for i=2,3,…,ni=2,3,\dots,ni=2,3,…,n

Output
Print the xor of all window xors.
Constraints

1≤k≤n≤1071 \le k \le n \le 10^71≤k≤n≤107
0≤x,a,b≤1090 \le x, a, b \le 10^90≤x,a,b≤109
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
8 5
3 7 1 11

Output:
0

Explanation: The input array is [3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6]. The windows are [3,0,1,8,2][3,0,1,8,2][3,0,1,8,2], [0,1,8,2,4][0,1,8,2,4][0,1,8,2,4], [1,8,2,4,7][1,8,2,4,7][1,8,2,4,7] and [8,2,4,7,6][8,2,4,7,6][8,2,4,7,6], and their xors are 888, 151515, 888 and 151515. Thus, the answer is 8⊕15⊕8⊕15=08 \oplus 15 \oplus 8 \oplus 15 = 08⊕15⊕8⊕15=0.
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
    int n , k;
    ll x , a , b , c;
    cin >> n >> k >> x >> a >> b >> c;
    ll ans = 0;
    vector<ll>v(n);
    v[0] = x;
    for (int i = 1;i < n;i++) {
        v[i] = (v[i - 1] * a + b) % c;
    }
    ll sum = 0;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            ans ^= sum;
            sum ^= v[i - k];
        }
        sum ^= v[i];
    }
    ans ^= sum;
    cout << ans << '\n';
}