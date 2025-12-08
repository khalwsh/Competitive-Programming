/* problem statement text */
/*
CSES - Counting Patterns

Time limit: 1.00 s
Memory limit: 512 MB

Given a string and patterns, count for each pattern the number of positions where it appears in the string.
Input
The first input line has a string of length nnn.
The next input line has an integer kkk: the number of patterns. Finally, there are kkk lines that describe the patterns.
The string and the patterns consist of characters a–z.
Output
For each pattern, print the number of positions.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤k≤5⋅1051 \le k \le 5 \cdot 10^51≤k≤5⋅105
the total length of the patterns is at most 5⋅1055 \cdot 10^55⋅105

Example
Input:
aybabtu
3
bab
abc
a

Output:
1
0
2
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
 
int get(const string &p) {
    int cur = 0;
    for (auto &val: p) {
        if (st[cur].nxt[val - 'a'] == -1)return 0;
        cur = st[cur].nxt[val - 'a'];
    }
    return cnt[cur];
}
 
void propagation() {
    // Order states by length (longest → shortest)
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });
 
    for (int v: order) {
        if (st[v].link != -1) {
            cnt[st[v].link] += cnt[v];
        }
    }
}
 
int main() {
    PRE();
    string s;
    cin >> s;
    build(s);
    propagation();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string p;
        cin >> p;
        cout << get(p) << '\n';
    }
}