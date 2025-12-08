/* problem statement text */
/*
CSES - Planets Queries I

Time limit: 1.00 s
Memory limit: 512 MB

You are playing a game consisting of nnn planets. Each planet has a teleporter to another planet (or the planet itself).
Your task is to process qqq queries of the form: when you begin on planet xxx and travel through kkk teleporters, which planet will you reach?
Input
The first input line has two integers nnn and qqq: the number of planets and queries. The planets are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The second line has nnn integers t1,t2,…,tnt_1,t_2,\dots,t_nt1​,t2​,…,tn​: for each planet, the destination of the teleporter. It is possible that ti=it_i=iti​=i.
Finally, there are qqq lines describing the queries. Each line has two integers xxx and kkk: you start on planet xxx and travel through kkk teleporters.
Output
Print the answer to each query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤ti≤n1 \le t_i \le n1≤ti​≤n
1≤x≤n1 \le x \le n1≤x≤n
0≤k≤1090 \le k \le 10^90≤k≤109

Example
Input:
4 3
2 1 1 4
1 2
3 4
4 1

Output:
1
2
4
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 1 , k = 30;
int n , q;
vector<int>adj[N];
int up[k][N];
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        up[0][i] = x - 1;
    }
    for(int i = 1;i < k;i++) {
        for(int j = 0;j < n;j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    while(q--) {
        int node , kth;cin>>node>>kth;
        node--;
        for(int i = 0;i < k;i++) {
            if(kth & (1<<i)) {
                node = up[i][node];
            }
        }
        cout<<node + 1<<'\n';
    }
}