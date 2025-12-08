/* problem statement text */
/*
CSES - Substring Order I

Time limit: 1.00 s
Memory limit: 512 MB

You are given a string of length nnn. If all of its distinct substrings are ordered lexicographically, what is the kkkth smallest of them?
Input
The first input line has a string of length nnn that consists of characters a–z.
The second input line has an integer kkk.
Output
Print the kkkth smallest distinct substring in lexicographical order.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤k≤n(n+1)21 \le k \le \frac{n(n+1)}{2}1≤k≤2n(n+1)​
It is guaranteed that kkk does not exceed the number of distinct substrings.

Example
Input:
babaacbaab
10

Output:
aba

Explanation: The 10 smallest distinct substrings in order are a, aa, aab, aac, aacb, aacba, aacbaa, aacbaab, ab, and aba.
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
 
// ------------------------- Suffix Automaton Template -------------------------
//
// A state in the Suffix Automaton (SAM):
// len        : Length of the longest substring in this equivalence class
// link       : Suffix link (points to the largest proper suffix state , another class)
// first_pos  : End position of the substring's first appearance in the text
// nxt[26]    : Transitions for each character (fixed for lowercase 'a'–'z')
// is_clone   : True if this state is a clone (created during split).
//              → Clone states are technical duplicates; skip them if you only
//                want distinct end positions.
//
// Optional auxiliary arrays (not included in this template but often useful):
// cnt[cur]       : Initialize as 1 for each state. After propagating through
//                  suffix links, it stores the number of occurrences of all
//                  substrings represented by this state.
// is_terminal[cur]: Marks this state as terminal (i.e., corresponds to a suffix).
//                  → A suffix in SAM is a path from the root to a terminal state.
// pos_state[pos] : Maps text position `pos` to the state representing the
//                  prefix ending at that position.
//                  → A prefix in SAM is a path from the root to pos_state[pos].
//
// ------------------------------------------------------------------------------
 
struct state {
    int len, link, first_pos;
    bool is_clone;
    int nxt[26];
};
 
const int MAXN = 2e5 + 9;
state st[2 * MAXN];
int cnt[MAXN], is_terminal[MAXN], pos_state[MAXN];
int sz, last;
 
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    fill(st[0].nxt, st[0].nxt + 26, -1);
 
    for (int i = 0; i < sz; ++i) {
        cnt[i] = 0;
        is_terminal[i] = 0;
    }
 
    sz = 1;
    last = 0;
}
 
void sa_extend(char c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    st[cur].is_clone = false;
    fill(st[cur].nxt, st[cur].nxt + 26, -1);
 
    cnt[cur] = 1;
    is_terminal[cur] = 1;
    pos_state[pos] = cur;
 
    int p = last, letter = c - 'a';
    while (p != -1 && st[p].nxt[letter] == -1) {
        st[p].nxt[letter] = cur;
        p = st[p].link;
    }
 
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[letter];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            copy(st[q].nxt, st[q].nxt + 26, st[clone].nxt);
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;
            st[clone].is_clone = true;
 
            while (p != -1 && st[p].nxt[letter] == q) {
                st[p].nxt[letter] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void build(const string &s) {
    sa_init();
    for (int i = 0; i < (int) s.size(); i++) {
        sa_extend(s[i], i);
    }
}
 
ll dp[MAXN];
 
ll solve(int cur) {
    ll res = 1;
    ll &ret = dp[cur];
    if (~ret) return ret;
    for (int i = 0; i < 26; i++) {
        if (st[cur].nxt[i] != -1) {
            res += solve(st[cur].nxt[i]);
        }
    }
    return ret = res;
}
 
string res;
 
void build(int cur, ll rem) {
    if (rem <= 0) return;
    for (int i = 0; i < 26; i++) {
        int u = st[cur].nxt[i];
        if (u == -1) continue;
        ll cnt = solve(u);
        if (cnt >= rem) {
            res += char('a' + i);
            build(u, rem - 1);
            return;
        }
        rem -= cnt;
    }
}
 
string get(ll k) {
    ll all = solve(0) - 1;
    assert(all >= k);
    build(0, k);
    return res;
}
 
 
int main() {
    PRE();
    string s;
    memset(dp, -1, sizeof dp);
    cin >> s;
    build(s);
    ll k;
    cin >> k;
    cout << get(k);
}