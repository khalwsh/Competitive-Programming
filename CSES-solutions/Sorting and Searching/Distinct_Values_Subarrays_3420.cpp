/* problem statement text */
/*
CSES - Distinct Values Subarrays

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, count the number of subarrays where each element is dictinct.
Input
The first line has an integer nnn: the array size.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array contents.
Output
Print the number of subarrays with distinct elements.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
4
1 2 1 3

Output:
8

Explanation: The subarrays are [1][1][1] (two times), [2][2][2], [3][3][3], [1,2][1,2][1,2], [1,3][1,3][1,3], [2,1][2,1][2,1] and [2,1,3][2,1,3][2,1,3].
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
int main(){
    PRE();
    int n;cin >> n;
    map<int ,int>mp;
    ll res = 0;
    int left = 0;
    vector<int>v(n);
    for (int i = 0;i < n;i++) {
        int x;cin >> x;mp[x]++;
        v[i] = x;
        while (mp.size() != i - left + 1) {
            mp[v[left]]--;
            if (mp[v[left]] == 0) mp.erase(v[left]);
            left++;
        }
        res += i - left + 1;
    }
    cout << res << '\n';
}