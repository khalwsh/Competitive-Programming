/* problem statement text */
/*
CSES - Sliding Window Distinct Values

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the number of distinct values in each window of kkk elements, from left to right.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print n−k+1n-k+1n−k+1 values: the numbers of distinct values.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
1 2 3 2 5 2 2 2

Output:
3 2 3 2 2 1
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
    cin >> n >> k;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    map<int , int>freq;
    for (int i = 0;i < n;i++) {
        if (i >= k) {
            cout << freq.size() << ' ';
            freq[v[i - k]]--;
            if (freq[v[i - k]] == 0) freq.erase(v[i - k]);
        }
        freq[v[i]]++;
    }
    cout << freq.size() << ' ';
}