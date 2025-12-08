/* problem statement text */
/*
CSES - Sliding Window Mex

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the mex of each window of kkk elements, from left to right.
The mex is the smallest nonnegative integer that does not appear in the array. For example, the mex for [3,1,4,3,0,5][3,1,4,3,0,5][3,1,4,3,0,5] is 222.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print n−k+1n-k+1n−k+1 values: the mex values.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109

Example
Input:
8 3
1 2 1 0 5 1 1 0

Output:
0 3 2 2 0 2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
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
const int N = 4e5 + 1;
int lst[N];
int main() {
    PRE();
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    memset(lst , -1 , sizeof lst);
    for (int i = 0; i < n; i++) cin >> v[i];
    set<int>all;
    for (int i = 0;i < N ;i++) all.insert(i);
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            cout << *all.begin() << " ";
            if (v[i - k] < N && lst[v[i - k]] == i - k ) all.insert(v[i - k]);
        }
        if (v[i] < N) {
            lst[v[i]] = i;
            if (all.count(v[i]))
             all.erase(v[i]);
        }
    }
    cout << *all.begin() << " ";
}