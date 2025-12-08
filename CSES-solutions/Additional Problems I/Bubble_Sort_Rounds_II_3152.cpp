/* problem statement text */
/*
CSES - Bubble Sort Rounds II

Time limit: 1.00 s
Memory limit: 512 MB

Bubble sort is a sorting algorithm that consists of a number of rounds. On each round the algorithm scans the array from left to right and swaps any adjacent elements that are in the wrong order.
Given an array of nnn integers, find out the contents of the array after kkk bubble sort rounds.
Input
The first line has two integers nnn and kkk: the array size and the number of rounds.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array contents.
Output
Print nnn integers: the contents of the array after kkk rounds.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤k≤1090 \le k \le 10^90≤k≤109
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
5 2
3 2 4 1 4

Output:
2 1 3 4 4
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
 
vector<int> get(const vector<int>& a, long long k) {
    int n = (int)a.size();
    if (k >= n) {
        vector<int> b = a;
        sort(b.begin(), b.end());
        return b;
    }
    vector<int> res; res.reserve(n);
    using P = pair<int,int>;
    auto cmp = [](const P &x, const P &y){
        if (x.first != y.first) return x.first > y.first;
        return x.second > y.second;
    };
    priority_queue<P, vector<P>, decltype(cmp)> pq(cmp);
 
    int init = (int)min<long long>(n, k + 1);
    for (int i = 0; i < init; ++i) pq.emplace(a[i], i);
    int next_idx = (int)(k + 1);
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        res.push_back(p.first);
        if (next_idx < n) {
            pq.emplace(a[next_idx], next_idx);
            ++next_idx;
        }
    }
    return res;
}
int main() {
    PRE();
    int n;cin >> n;
    vector<int>v(n);
    ll k; cin >> k;
    for (auto &val : v) cin >> val;
    for (auto &val : get(v , k)) cout << val << " ";
}