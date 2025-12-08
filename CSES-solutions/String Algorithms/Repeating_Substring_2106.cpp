/* problem statement text */
/*
CSES - Repeating Substring

Time limit: 1.00 s
Memory limit: 512 MB

A repeating substring is a substring that occurs in two (or more) locations in the string. Your task is to find the longest repeating substring in a given string.
Input
The only input line has a string of length nnn that consists of characters a–z.
Output
Print the longest repeating substring. If there are several possibilities, you can print any of them. If there is no repeating substring, print −1-1−1.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105

Example
Input:
cabababc

Output:
abab
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
 
vector<int> buildSuffixArray(string s) {
    int n = s.size(); s += "$";
    vector<int> p(n+1), c(n+1), c1(n+1), cnt(max(256, n+1)), p1(n+1);
    for(int i = 0; i <= n; i++) p[i] = i, c[i] = s[i];
 
    for(int k = 0; (1 << k) <= n; k++) {
        int len = 1 << k;
 
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[min(n, p[i] + len)]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p1[--cnt[c[min(n, p[i] + len)]]] = p[i];
 
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i <= n; i++) cnt[c[p1[i]]]++;
        for(int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i = n; i >= 0; i--) p[--cnt[c[p1[i]]]] = p1[i];
 
        c1[p[0]] = 0;
        for(int i = 1; i <= n; i++)
            c1[p[i]] = c1[p[i-1]] + (c[p[i]] != c[p[i-1]] || c[min(n,p[i]+len)] != c[min(n,p[i-1]+len)]);
        c.swap(c1);
        if(c[p[n]] == n) break;
    }
 
    vector<int> res;
    for(int i = 1; i <= n; i++) res.push_back(p[i]);
    return res;
}
vector<int> Kasai(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if(rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}
 
int main() {
    PRE();
    string s; cin >> s;
    auto suf = buildSuffixArray(s);
    auto lcp = Kasai(s , suf);
    int mx = -1;
    for (int i = 0;i < lcp.size();i++) {
        if (lcp[i]) {
            if (mx == -1 || lcp[mx] < lcp[i]) {
                mx = i;
            }
        }
    }
    if (mx == -1) cout << -1;
    else cout << s.substr(suf[mx] , lcp[mx]);
 
}