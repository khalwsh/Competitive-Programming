/* problem statement text */
/*
CSES - Maximum Xor Subarray

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to find the maximum xor sum of a subarray.
Input
The first line has an integer nnn: the size of the array.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Output
Print one integer: the maximum xor sum in a subarray.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109

Example
Input:
4
5 1 5 9

Output:
13
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
struct Trie {
    Trie *link[2];
    int cnt;
    int leaf;
    Trie(const Trie& o) : cnt(o.cnt), leaf(o.leaf) {
        link[0] = o.link[0] ? new Trie(*o.link[0]) : nullptr;
        link[1] = o.link[1] ? new Trie(*o.link[1]) : nullptr;
    }
    static const int BITS = 30;
    Trie() {
        for (int i = 0; i < 2; ++i) {
            link[i] = nullptr;
        }
        cnt = 0;
        leaf = 0;
    }
 
    void insert(int x, int idx = BITS) {
        if (idx == -1) {
            cnt++;
            leaf++;
            return;
        }
        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr)link[ch] = new Trie();
        link[ch]->insert(x, idx - 1);
 
        cnt++;
    }
 
    bool erase(int x, int idx = BITS) {
        if (idx == -1) {
            cnt--;
            leaf--;
            return true;
        }
 
        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr) {
            return false;
        }
        if (link[ch]->erase(x, idx - 1)) {
            cnt--;
            if (link[ch]->cnt == 0) {
                delete link[ch];
                link[ch] = nullptr;
            }
            return true;
        }
        return false;
    }
 
    int find(int x, int idx = BITS) {
        if (idx == -1)return cnt;
 
        bool ch = ((1ll << idx) & x);
        if (link[ch] == nullptr)return 0;
        return link[ch]->find(x, idx - 1);
    }
 
    int MinXor(int x, int idx = BITS) {
        if (idx == -1) {
            return 0;
        }
 
        bool ch = ((1ll << idx) & x);
 
        if (link[ch] != nullptr) {
            return link[ch]->MinXor(x, idx - 1);
        } else if (link[!ch] != nullptr)return link[!ch]->MinXor(x, idx - 1) | (1ll << idx);
        return x;
    }
 
    int MaxXor(int x, int idx = BITS) {
        if (idx == -1) {
            return 0;
        }
 
        bool ch = ((1ll << idx) & x);
 
        if (link[!ch] != nullptr) {
 
            return link[!ch]->MaxXor(x, idx - 1) | (1ll << idx);
        } else if (link[ch] != nullptr)return link[ch]->MaxXor(x, idx - 1);
        return 0;
    }
 
 
} ;
int main() {
    PRE();
    int x = 0;
    Trie t;
    t.insert(x);
    int n;cin >> n;
    int res = 0;
    for (int i = 0;i < n;i++) {
        int y; cin >> y;
        x ^= y;
        res = max(res , t.MaxXor(x));
        t.insert(x);
    }
    cout << res << '\n';
}