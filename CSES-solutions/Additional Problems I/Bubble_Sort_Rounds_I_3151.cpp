/* problem statement text */
/*
CSES - Bubble Sort Rounds I

Time limit: 1.00 s
Memory limit: 512 MB

Bubble sort is a sorting algorithm that consists of a number of rounds. On each round the algorithm scans the array from left to right and swaps any adjacent elements that are in the wrong order.
Given an array of nnn integers, calculate the number of bubble sort rounds needed to sort the array.
Input
The first line has an integer nnn: the array size.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array contents.
Output
Print one integer: the number of rounds.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
5
3 2 4 1 4

Output:
3

Explanation: Bubble sort needs three rounds to sort this array. The array contents after each round are [2,3,1,4,4][2,3,1,4,4][2,3,1,4,4], [2,1,3,4,4][2,1,3,4,4][2,1,3,4,4], and [1,2,3,4,4][1,2,3,4,4][1,2,3,4,4].
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
 
int bubble_passes(const vector<int>& a){
    int n = a.size();
    vector<pair<int,int>> p;
    for(int i=0;i<n;i++) p.emplace_back(a[i], i);
    stable_sort(p.begin(), p.end(), [](const auto& x, const auto& y){
        return x.first < y.first;
    });
    int res = 0;
    for(int i = 0; i < n; ++i){
        int o = p[i].second;
        res = max(res, o - i);
    }
    return res;
}
int main() {
    PRE();
    int n;cin >> n;
    vector<int>v(n);
    for (auto &val : v) cin >> val;
    cout << bubble_passes(v);
}