/* problem statement text */
/*
CSES - Raab Game I

Time limit: 1.00 s
Memory limit: 512 MB

Consider a two player game where each player has nnn cards numbered 1,2,…,n1,2,\dots,n1,2,…,n. On each turn both players place one of their cards on the table. The player who placed the higher card gets one point. If the cards are equal, neither player gets a point. The game continues until all cards have been played.
You are given the number of cards nnn and the players' scores at the end of the game, aaa and bbb. Your task is to give an example of how the game could have played out.
Input
The first line contains one integer ttt: the number of tests.
Then there are ttt lines, each with three integers nnn, aaa and bbb.
Output
For each test case print YES if there is a game with the given outcome and NO otherwise.
If the answer is YES, print an example of one possible game. Print two lines representing the order in which the players place their cards. You can give any valid example.
Constraints

1≤t≤10001 \le t \le 10001≤t≤1000
1≤n≤1001 \le n \le 1001≤n≤100
0≤a,b≤n0 \le a,b \le n0≤a,b≤n

Example
Input:
5
4 1 2
2 0 1
3 0 0
2 1 1
4 4 1

Output:
YES
1 4 3 2
2 1 3 4
NO
YES
1 2 3
1 2 3
YES
1 2
2 1
NO
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
    int t;cin >> t;
    while (t--) {
        int n;cin >> n;
        int a , b; cin >> a >> b;
        if (a + b > n || (a == 0 && b != 0) || (b == 0 && a != 0)) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 1;i <= n;i++) cout << i << " ";
            cout << '\n';
            for (int i = 1;i <= b;i++) cout << a + i << " ";
            for (int i = 1;i <= a;i++) cout << i << " ";
            for (int i = a + b + 1;i <= n;i++) cout << i << " ";
            cout << '\n';
        }
    }
}