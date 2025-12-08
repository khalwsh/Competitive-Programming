/* problem statement text */
/*
CSES - String Matching

Time limit: 1.00 s
Memory limit: 512 MB

Given a string and a pattern, your task is to count the number of positions where the pattern occurs in the string.
Input
The first input line has a string of length nnn, and the second input line has a pattern of length mmm. Both of them consist of characters a–z.
Output
Print one integer: the number of occurrences.
Constraints

1≤n,m≤1061 \le n,m \le 10^61≤n,m≤106

Example
Input:
saippuakauppias
pp

Output:
2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
 
vector<int>failure;
 
 
int main() {
    PRE();
    string s , t;cin>>s>>t;
 
    failure = vector<int>(t.size());
    // failure[0] = 0;
    for(int i = 1;i < failure.size();i++) {
        int len = failure[i - 1];
        while(len > 0 && t[i] != t[len]) {
            len = failure[len - 1];
        }
        if(t[i] == t[len])len++;
        failure[i] = len;
    }
 
    int len = 0;
    vector<int>v;
    for(int i = 0;i < s.size();i++) {
        while(len > 0 && s[i] != t[len]) {
            len = failure[len - 1];
        }
        if(s[i] == t[len]) {
            len++;
        }
        if(len == t.size()) {
            v.emplace_back(i - t.size() + 1);
            len = failure[len - 1];
        }
    }
    cout<<v.size()<<'\n';
}