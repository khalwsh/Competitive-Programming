/* problem statement text */
/*
CSES - Shortest Subsequence

Time limit: 1.00 s
Memory limit: 512 MB

You are given a DNA sequence consisting of characters A, C, G, and T.
Your task is to find the shortest DNA sequence that is not a subsequence of the original sequence.
Input
The only input line contains a DNA sequence with nnn characters.
Output
Print the shortest DNA sequence that is not a subsequence of the original sequence. If there are several solutions, you may print any of them.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
ACGTACGT

Output:
AAA
*/
#include <bits/stdc++.h>
using namespace std;
 
const int ALPH = 4;
const int INF = 1e9;
string letters = "ACGT";
 
int idx(char c){
    if(c == 'A') return 0;
    if(c == 'C') return 1;
    if(c == 'G') return 2;
    return 3; // 'T'
}
 
string s;
int n;
vector<array<int,ALPH>> Nxt;
vector<int> dp;
 
int solve(int pos){
    int &res = dp[pos];
    if(res != -1) return res;
    for(int c = 0; c < ALPH; ++c){
        if(Nxt[pos][c] == -1){
            return res = 1;
        }
    }
    int best = INF;
    for(int c = 0; c < ALPH; ++c){
        int nxt = Nxt[pos][c];
        best = min(best, 1 + solve(nxt + 1));
    }
    return res = best;
}
 
string build(int pos){
    for(int c = 0; c < ALPH; ++c){
        int nxt = Nxt[pos][c];
        if(nxt == -1){
            return string(1, letters[c]);
        }
        if(1 + solve(nxt + 1) == solve(pos)){
            return letters[c] + build(nxt + 1);
        }
    }
    return "";
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    n = (int)s.size();
    Nxt.assign(n + 1, array<int,ALPH>());
    for(int c = 0; c < ALPH; ++c) Nxt[n][c] = -1;
    for(int i = n - 1; i >= 0; --i) {
        Nxt[i] = Nxt[i + 1];
        Nxt[i][ idx(s[i]) ] = i;
    }
 
    dp.assign(n + 1, -1);
    solve(0);
    string ans = build(0);
    cout << ans << "\n";
}