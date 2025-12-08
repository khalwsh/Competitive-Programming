/* problem statement text */
/*
CSES - Substring Order II

Time limit: 1.00 s
Memory limit: 512 MB

You are given a string of length nnn. If all of its substrings (not necessarily distinct) are ordered lexicographically, what is the kkkth smallest of them?
Input
The first input line has a string of length nnn that consists of characters a–z.
The second input line has an integer kkk.
Output
Print the kkkth smallest substring in lexicographical order.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤k≤n(n+1)21 \le k \le \frac{n(n+1)}{2}1≤k≤2n(n+1)​

Example
Input:
baabaa
10

Output:
ab

Explanation: The 10 smallest substrings in order are a, a, a, a, aa, aa, aab, aaba, aabaa, and ab.
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
 
const int MAXN = 5e5 + 9;
state st[2 * MAXN];
int cnt[2 * MAXN], is_terminal[2 * MAXN], pos_state[2 * MAXN];
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
 
void propagation() {
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });
    for (int v: order) {
        if (st[v].link != -1) cnt[st[v].link] += cnt[v];
    }
}
 
ll dp[MAXN];
 
ll solve(int v) {
    if (dp[v] != -1) return dp[v];
    ll res = 0;
    for (int c = 0; c < 26; c++) {
        int u = st[v].nxt[c];
        if (u != -1) {
            res += cnt[u]; // substrings of length 1 from this edge
            res += solve(u); // longer substrings
        }
    }
    return dp[v] = res;
}
 
void printKth(int v, ll k) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int u = st[v].nxt[ch - 'a'];
        if (u == -1) continue;
        ll total = cnt[u] + solve(u);
        if (k <= total) {
            cout << ch;
            if (k <= cnt[u]) return; // stop here
            printKth(u, k - cnt[u]);
            return;
        } else {
            k -= total;
        }
    }
}
 
int main() {
    PRE();
    string s;
    cin >> s;
    sa_init();
    for (char c: s) sa_extend(c, 0);
 
    propagation();
    memset(dp, -1, sizeof dp);
 
    ll k;
    cin >> k;
    printKth(0, k);
    cout << "\n";
}