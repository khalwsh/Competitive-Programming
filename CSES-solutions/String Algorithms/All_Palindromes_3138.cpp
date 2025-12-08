/* problem statement text */
/*
CSES - All Palindromes

Time limit: 1.00 s
Memory limit: 512 MB

Given a string, calculate for each position the length of the longest palindrome that ends at that position.
Input
The only line contains a string of length nnn. Each character is one of a–z.
Output
Print nnn numbers: the length of each palindrome.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105

Example
Input:
ababbababaa

Output:
1 1 3 3 2 4 6 8 5 5 2
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
 
struct PalindromicTree {
    // len (length of the maximum palindromic suffix at that position)
    // link (fail link the next smaller palindrome) [node index]
    // cnt (how many distinct suffix palindrome that end at that position)
    // oc (how many palindrome in the entire string that match this palindrome) but call calc first
    // st , en start and end indices of the palindrome in the input string
    struct node {
        int len, st, en, link, cnt, oc;
        map<char, int> nxt;
    };
 
    vector<node> t; // nodes one based indexing
    int sz, last; // sz = current highest node index; last = node for longest pal-suffix of current prefix
    string s; // built string
 
    vector<int> char_node; // zero base
    // for each position i, char_node[i] = node index of the longest palindromic suffix ending at i
 
    PalindromicTree() {
        t.assign(3, {});
        sz = 2, last = 2;
        t[1].len = -1, t[1].link = 1;
        t[2].len = 0, t[2].link = 1;
    }
 
    stack<array<int, 4> > st; // history for roll back
 
    int push(char ch) {
        s.push_back(ch);
        int cur = last, curlen = 0, pos = s.length() - 1;
 
        while (1) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
            cur = t[cur].link;
        }
        if (t[cur].nxt[ch]) {
            st.push({0, last});
 
            last = t[cur].nxt[ch];
            t[last].oc++;
            char_node.push_back(last);
            return t[last].len;
        }
 
        st.push({1, last, cur, (int) ch});
 
        sz++;
        last = sz;
        t.push_back({});
        char_node.push_back(last);
 
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
 
        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            return t[sz].len;
        }
 
        while (1) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[sz].link = t[cur].nxt[ch];
                break;
            }
        }
 
        t[sz].cnt = 1 + t[t[sz].link].cnt;
 
        return t[sz].len;
    }
 
    void pop() {
        if (st.empty()) return;
 
        auto &curr = st.top();
        if (curr[0] == 0) {
            t[last].oc--;
            last = curr[1];
            char_node.pop_back();
        } else {
            last = curr[1];
            t[curr[2]].nxt[(char) curr[3]] = 0;
            t.pop_back();
            char_node.pop_back();
            sz--;
        }
        st.pop();
        s.pop_back();
    }
 
    // Don't forget to call this
    void calc_occurrences() {
        for (int i = sz; i >= 3; i--) t[t[i].link].oc += t[i].oc;
    }
 
    ll calc_pals() {
        ll ans = 0;
        for (int i = 0; i < s.length(); ++i) {
            ans += t[char_node[i]].oc;
        }
        return ans;
    }
 
    int calc_dist_pals() {
        return sz - 2;
    }
};
 
int main() {
    PRE();
    string s;
    cin >> s;
    PalindromicTree pt;
    for (auto &val: s) {
        cout << pt.push(val) << " ";
    }
}