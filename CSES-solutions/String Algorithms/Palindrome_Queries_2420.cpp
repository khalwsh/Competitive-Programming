/* problem statement text */
/*
CSES - Palindrome Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given a string that consists of nnn characters between a–z. The positions of the string are indexed 1,2,…,n1,2,\dots,n1,2,…,n.
Your task is to process mmm operations of the following types:

Change the character at position kkk to xxx
Check if the substring from position aaa to position bbb is a palindrome

Input
The first input line has two integers nnn and mmm: the length of the string and the number of operations.
The next line has a string that consists of nnn characters.
Finally, there are mmm lines that describe the operations. Each line is of the form "1 kkk xxx" or "2 aaa bbb".
Output
For each operation 2, print YES if the substring is a palindrome and NO otherwise.
Constraints

1≤n,m≤2⋅1051 \le n, m \le 2 \cdot 10^51≤n,m≤2⋅105
1≤k≤n1 \le k \le n1≤k≤n
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
7 5
aybabtu
2 3 5
1 3 x
2 3 5
1 5 x
2 3 5

Output:
YES
NO
YES
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
const ll HASH = 257, MOD = 1e9 + 7;
 
const int md = 1e9+7;
int B = 73; //Sheldon prime (lol)
const int mxN = 1e6+6;
ll pB[mxN];
struct {
    ll bit[mxN] = {0};
 
    void update(int k, ll x) {
        x %= md;
        if (x < md) x += md;
        for (; k < mxN; k += k&-k) {
            (bit[k] += x) %= md;
        }
    }
 
    ll query(int k) {
        ll s = 0;
        for (; k > 0; k -= k&-k)
            (s += bit[k]) %= md;
        return s;
    }
} pre, suf;
 
int main() {
    PRE();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    B = uniform_int_distribution<int>(73, 7337)(rng);
    int n, t; cin>>n>>t;
 
    string s; cin>>s;
    pB[0] = 1;
    for (int i = 1; i < mxN; i++)
        pB[i] = pB[i-1] * B % md;
 
    for (int i = 0; i < n; i++) {
        pre.update(i+1, (s[i]-'a'+1) * pB[i]);
        suf.update(i+1, (s[i]-'a'+1) * pB[n-i-1]);
    }
    while (t--) {
        int ch; cin>>ch;
        if (ch == 1) {
            int k; char x;
            cin>>k>>x; k--;
            pre.update(k+1, -(s[k]-'a'+1) * pB[k]);
            pre.update(k+1, (x-'a'+1) * pB[k]);
            suf.update(k+1, -(s[k]-'a'+1) * pB[n-k-1]);
            suf.update(k+1, (x-'a'+1) * pB[n-k-1]);
            s[k] = x;
        }
        else {
            int x, y; cin>>x>>y;
            ll h1 = (pre.query(y) - pre.query(x-1) + md) % md;
            ll m1 = pB[x-1];
            ll h2 = (suf.query(y) - suf.query(x - 1) + md) % md;
            ll m2 = pB[n-y];
            cout << (h1 * m2 % md == h2 * m1 % md ? "YES" : "NO" ) << '\n';
        }
    }
}