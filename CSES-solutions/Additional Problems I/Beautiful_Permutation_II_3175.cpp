/* problem statement text */
/*
CSES - Beautiful Permutation II

Time limit: 1.00 s
Memory limit: 512 MB

A permutation of integers 1,2,…,n1,2,\ldots,n1,2,…,n is called beautiful if there are no adjacent elements whose difference is 111.
Given nnn, construct the lexicographically minimal beautiful permutation if such a permutation exists.
Input
The only line contains an integer nnn.
Output
Print the lexicographically minimal beautiful permutation of integers 1,2,…,n1,2,\ldots,n1,2,…,n. If there is no such permutation, print "NO SOLUTION".
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example 1
Input:
5

Output:
1 3 5 2 4
Example 2
Input:
3

Output:
NO SOLUTION
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
    int n;cin >> n;
    set<int> rem;
    for (int i = 1;i <= n;i++) {
        rem.insert(i);
    }
    int lst = -100;
    for (int i = 0;i < n - 6;i++) {
        auto it = rem.begin();
        while (abs(lst - *it) == 1) it++;
        cout << *it << " ";
        lst = *it;
        rem.erase(it);
    }
    vector<int>v;
    for (auto &val : rem) v.emplace_back(val);
    vector<int> res;
    sort(v.begin() , v.end());
    do {
        int temp = lst;
        bool ok = true;
        for (auto &val : v) {
            if (abs(val - temp) == 1) ok = false;
            temp = val;
        }
        if (ok) {
            if (res.empty()) res = v;
            else res = min(res , v);
        }
    }while (next_permutation(v.begin() , v.end()));
    if (res.empty()) cout << "NO SOLUTION";
    else for (auto &val : res) cout << val << " ";
}