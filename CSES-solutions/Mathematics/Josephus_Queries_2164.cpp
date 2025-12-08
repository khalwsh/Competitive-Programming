/* problem statement text */
/*
CSES - Josephus Queries

Time limit: 1.00 s
Memory limit: 512 MB

Consider a game where there are nnn children (numbered 1,2,…,n1,2,\dots,n1,2,…,n) in a circle. During the game, every second child is removed from the circle, until there are no children left.
Your task is to process qqq queries of the form: "when there are nnn children, who is the kkkth child that will be removed?"
Input
The first input line has an integer qqq: the number of queries.
After this, there are qqq lines that describe the queries. Each line has two integers nnn and kkk: the number of children and the position of the child.
Output
Print qqq integers: the answer for each query.
Constraints

1≤q≤1051 \le q \le 10^51≤q≤105
1≤k≤n≤1091 \le k \le n \le 10^91≤k≤n≤109

Example
Input:
4
7 1
7 3
2 2
1337 1313

Output:
2
6
1
1107
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
 
ll f(ll n,ll k){
    if(n == 1) return 1;
    if(k <= (n + 1) / 2) {
        if(2 * k > n) return (2 * k) % n;
        else return 2 * k;
    }
    ll temp = f(n / 2,k - (n + 1) / 2);
    if(n % 2 == 1) return 2 * temp + 1;
    return 2 * temp - 1;
}
 
int main() {
    PRE();
    int q; cin >> q;
    while (q--) {
        int n , k; cin >> n >> k;
        cout << f(n , k) << '\n';
    }
}