/* problem statement text */
/*
CSES - Stick Game

Time limit: 1.00 s
Memory limit: 512 MB

Consider a game where two players remove sticks from a heap. The players move alternately, and the player who removes the last stick wins the game.
A set P={p1,p2,…,pk}P=\{p_1,p_2,\ldots,p_k\}P={p1​,p2​,…,pk​} determines the allowed moves. For example, if P={1,3,4}P=\{1,3,4\}P={1,3,4}, a player may remove 111, 333 or 444 sticks.
Your task is find out for each number of sticks 1,2,…,n1,2,\dots,n1,2,…,n if the first player has a winning or losing position.
Input
The first input line has two integers nnn and kkk: the number of sticks and moves.
The next line has kkk integers p1,p2,…,pkp_1,p_2,\dots,p_kp1​,p2​,…,pk​ that describe the allowed moves. All integers are distinct, and one of them is 111.
Output
Print a string containing nnn characters: W means a winning position, and L means a losing position.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106
1≤k≤1001 \le k \le 1001≤k≤100
1≤pi≤n1 \le p_i \le n1≤pi​≤n

Example
Input:
10 3
1 3 4

Output:
WLWWWWLWLW
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , k;
    cin>>n>>k;
    vector<bool>w(n + 1);
    w[0] = false;
    vector<int>moves;
    for(int i = 0;i < k;i++) {
        int x;cin>>x;
        moves.emplace_back(x);
    }
    for(int i = 1;i <= n;i++) {
        bool ret = w[i];
        for(auto &val:moves) {
            if(i - val >= 0)ret = ret || !w[i - val];
            if(ret)break;
        }
        cout<<(ret ? "W" : "L");
        w[i] = ret;
    }
}