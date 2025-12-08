/* problem statement text */
/*
CSES - Sliding Window Mode

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the mode each window of kkk elements, from left to right.
The mode is the most frequent element in an array. If there are several possible modes, choose the smallest of them.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print n−k+1n-k+1n−k+1 values: the modes.
Constraints

1≤k≤n≤2⋅1051 \le k \le n \le 2 \cdot 10^51≤k≤n≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109

Example
Input:
8 3
1 2 3 2 5 2 4 4

Output:
1 2 2 2 2 4
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
 
struct WindowFreq {
    map<int, int> freq;
    map<int, multiset<int>> fte;
 
    void add(int x) {
        int old = freq[x];
        if (old > 0) {
            auto it = fte.find(old);
            if (it != fte.end()) {
                auto mit = it->second.find(x);
                if (mit != it->second.end()) it->second.erase(mit);
                if (it->second.empty()) fte.erase(it);
            }
        }
        freq[x]++;
        fte[freq[x]].insert(x);
    }
 
    void remove(int x) {
        int old = freq[x];
        if (old == 0) return;
 
        auto it = fte.find(old);
        if (it != fte.end()) {
            auto mit = it->second.find(x);
            if (mit != it->second.end()) it->second.erase(mit);
            if (it->second.empty()) fte.erase(it);
        }
 
        freq[x]--;
        if (freq[x] == 0) {
            freq.erase(x);
            return;
        }
        fte[freq[x]].insert(x);
    }
 
    int getBest() const {
        if (fte.empty()) return -1;
        auto it = fte.rbegin();
        return *it->second.begin();
    }
 
    int uniqueCount() const {
        return (int)freq.size();
    }
};
 
int main() {
    PRE();
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
 
    WindowFreq wf;
 
    for (int i = 0; i < n; i++) {
        if (i >= k) {
            cout << wf.getBest() << ' ';
            wf.remove(v[i - k]);
        }
        wf.add(v[i]);
    }
    cout << wf.getBest() << ' ';
}