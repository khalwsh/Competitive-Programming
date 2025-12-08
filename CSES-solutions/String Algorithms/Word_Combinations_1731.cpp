/* problem statement text */
/*
CSES - Word Combinations

Time limit: 1.00 s
Memory limit: 512 MB

You are given a string of length nnn and a dictionary containing kkk words. In how many ways can you create the string using the words?
Input
The first input line has a string containing nnn characters between a–z.
The second line has an integer kkk: the number of words in the dictionary.
Finally there are kkk lines describing the words. Each word is unique and consists of characters a–z.
Output
Print the number of ways modulo 109+710^9+7109+7.
Constraints

1≤n≤50001 \le n \le 50001≤n≤5000
1≤k≤1051 \le k \le 10^51≤k≤105
the total length of the words is at most 10610^6106

Example
Input:
ababc
4
ab
abab
c
cb

Output:
2

Explanation: The possible ways are ab+ab+c and abab+c.
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
 
const int mod = 1e9 + 7;
 
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
 
    /// Returns index of longest word ending at each position, or -1 if none
    /// Time: O(|word|) where |word| is text length
    vector<int> find(string &word) {
        int node = 0;
        vector<int> res;
        for (auto &c: word) {
            node = v[node].nxt[c - first];
            res.push_back(v[node].end);
        }
        return res;
    }
 
    int solve(vector<string> &pats, string &word) {
        int n = word.size();
        auto r = find(word);
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < word.size(); ++i) {
            int ind = r[i];
            while (ind != -1) {
                dp[i + 1] += dp[i - (int) pats[ind].size() + 1];
                dp[i + 1] %= mod;
                ind = backup[ind];
            }
        }
        return dp[n];
    }
};
 
int main() {
    PRE();
    string text;
    cin >> text;
    int n;
    cin >> n;
    vector<string> pats;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        pats.emplace_back(s);
    }
    sort(pats.begin(), pats.end());
    pats.erase(unique(pats.begin(), pats.end()), pats.end());
    AhoCorasick aho(pats);
    cout << aho.solve(pats, text) << '\n';
}