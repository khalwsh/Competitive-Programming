/* problem statement text */
/*
CSES - Pattern Positions

Time limit: 1.00 s
Memory limit: 512 MB

Given a string and patterns, find for each pattern the first position (1-indexed) where it appears in the string.
Input
The first input line has a string of length nnn.
The next input line has an integer kkk: the number of patterns. Finally, there are kkk lines that describe the patterns.
The string and the patterns consist of characters a–z.
Output
Print the first position for each pattern (or −1-1−1 if it does not appear at all).
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
3
-1
1
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
 
const int N = 5e5 + 1;
int ans[N];
 
struct AhoCorasick {
    /// Modify these values based on input alphabet
    /// alpha: size of alphabet (26 for lowercase letters)
    /// first: first character of alphabet ('a' for lowercase letters)
    enum { alpha = 26, first = 'a' };
 
    struct Node {
        int nxt[alpha]; /// Next state transition for each character
        int suflink = 0; /// Suffix link points to longest proper suffix
        int start = -1; /// Start index of pattern in original array
        int end = -1; /// Index in backup of longest matched suffix pattern
        int nmatches = 0; ///Count of matched strings ending at this node
        int lvl = 0;
 
        Node(int v) {
            memset(nxt, v, sizeof nxt);
        }
    };
 
    vector<Node> v; /// Stores all nodes of the trie
    vector<int> backup;
    /// Stores pattern indices with longest matching suffixes
    /// Returns -1 if no match exists
    /// Note: All patterns must be distinct when using backup
 
    /// Inserts a pattern into the automaton
    /// Time: O(|s|) where |s| is pattern length
    void insert(string &s, int id) {
        int node = 0;
        int clvl = 0;
        for (auto &c: s) {
            int &m = v[node].nxt[c - first];
 
            ++clvl;
            if (m == -1) {
                node = m = v.size();
                v.emplace_back(-1);
                v.back().lvl = clvl;
            } else node = m;
        }
        if (v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end);
        v[node].end = id;
        v[node].nmatches++;
    }
 
    /// Builds Aho-Corasick automaton from patterns
    /// Time: O(26N) where N = sum of all pattern lengths
    /// - Creates suffix links
    /// - Allows duplicate patterns
    /// - For large alphabets, split symbols into chunks with sentinel bits
    AhoCorasick(vector<string> &pat) : v(1, -1) {
        for (int i = 0; i < pat.size(); ++i)
            insert(pat[i], i);
        v[0].suflink = v.size();
        v.emplace_back(0);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            int prv = v[node].suflink;
 
            for (int i = 0; i < alpha; ++i) {
                int &x = v[node].nxt[i], y = v[prv].nxt[i];
                if (x == -1) x = y;
                else {
                    v[x].suflink = y;
                    (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                    v[x].nmatches += v[y].nmatches;
                    q.push(x);
                }
            }
        }
    }
 
    // Returns index of longest word ending at each position, or -1 if none
    // Time: O(|word|) where |word| is text length
    vector<int> find(string &word) {
        int node = 0;
        vector<int> res;
        for (auto &c: word) {
            node = v[node].nxt[c - first];
            res.push_back(v[node].end);
        }
        return res;
    }
 
    void solve(string &text, vector<string> &pats) {
        auto r = find(text);
        for (int i = 0; i < text.size(); i++) {
            int ind = r[i];
            while (ind != -1) {
                if (ans[ind] == -1) ans[ind] = 1e9;
                ans[ind] = min(ans[ind], i - (int) pats[ind].size() + 2);
                ind = backup[ind];
            }
        }
    }
};
 
int main() {
    PRE();
    string s;
    cin >> s;
    int q;
    cin >> q;
    vector<string> pats;
    memset(ans, -1, sizeof ans);
    map<string, int> mp;
    vector<int> depend(q);
    for (int i = 0; i < q; i++) {
        string k;
        cin >> k;
        if (mp.count(k)) {
            depend[i] = mp[k];
        } else
            pats.emplace_back(k), depend[i] = (int) pats.size() - 1, mp[k] = depend[i];
    }
    AhoCorasick aho(pats);
    aho.solve(s, pats);
    for (int i = 0; i < q; i++)
        cout << ans[depend[i]] << '\n';
}