/* problem statement text */
/*
CSES - Sum of Two Values

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers, and your task is to find two values (at distinct positions) whose sum is xxx.
Input
The first input line has two integers nnn and xxx: the array size and the target sum.
The second line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the array values.
Output
Print two integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤x,ai≤1091 \le x,a_i \le 10^91≤x,ai​≤109

Example
Input:
4 8
2 7 5 1

Output:
2 4
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
vector<pair<int , int>>v;
int main() {
    PRE();
    int n , x;cin>>n>>x;
    for(int i = 0;i < n;++i) {
        int y;cin>>y;
        v.emplace_back(y , i);
    }
    sort(v.begin() , v.end());
    int p1 = 0 , p2 = v.size() - 1;
    while(p1 < p2) {
        if(v[p1].first + v[p2].first == x) {
            int l = v[p1].second , r = v[p2].second;
            if(l > r)swap(l , r);
            cout<<l + 1<<" "<<r + 1<<'\n';
            exit(0);
        }
        if(v[p1].first + v[p2].first > x) {
            p2--;
        }else
            p1++;
    }
    cout<<"IMPOSSIBLE\n";
}