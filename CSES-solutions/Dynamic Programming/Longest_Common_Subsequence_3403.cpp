/* problem statement text */
/*
CSES - Longest Common Subsequence

Time limit: 1.00 s
Memory limit: 512 MB

Given two arrays of integers, find their longest common subsequence.
A subsequence is a sequence of array elements from left to right that can contain gaps. A common subsequence is a subsequence that appears in both arrays.
Input
The first line has two integers nnn and mmm: the sizes of the arrays.
The second line has nnn integers a1,a2,…,ana_1,a_2,\dots,a_na1​,a2​,…,an​: the contents of the first array.
The third line has mmm integers b1,b2,…,bmb_1,b_2,\dots,b_mb1​,b2​,…,bm​: the contents of the second array.
Output
First print the length of the longest common subsequence.
After that, print an example of such a sequence. If there are several solutions, you can print any of them.
Constraints

1≤n,m≤10001 \le n,m \le 10001≤n,m≤1000
1≤ai,bi≤1091 \le a_i, b_i \le 10^91≤ai​,bi​≤109

Example
Input:
8 6
3 1 3 2 7 4 8 2
6 5 1 2 3 4

Output:
3
1 2 4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 1001;
int n , m;
int dp[N][N] , a[N] , b[N];
pair<int , int> parent[N][N];
 
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i <= n;i++) for (int j = 0;j <= m;j++)
        parent[i][j] = {-1 , -1};
    for (int i = 0;i < n;i++) cin >> a[i];
    for (int i = 0;i < m;i++) cin >> b[i];
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            if (a[i - 1] == b[j - 1]) {
                if (dp[i][j] < dp[i - 1][j - 1] + 1) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    parent[i][j] = {i - 1 , j - 1};
                }
            }else {
                if (dp[i][j] < dp[i][j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                    parent[i][j] = {i , j - 1};
                }
                if (dp[i][j] < dp[i - 1][j]) {
                    dp[i][j] = dp[i - 1][j];
                    parent[i][j] = {i - 1 , j};
                }
            }
        }
    }
    vector<int>seq;
    int mx = dp[n][m];
    pair<int , int>s = {n , m};
    while (seq.size() != mx) {
        auto [i , j] = parent[s.first][s.second];
        if (i == s.first - 1 && j == s.second - 1) seq.emplace_back(a[i]);
        s = {i , j};
    }
    reverse(seq.begin() , seq.end());
    cout<<mx<<'\n';
    for (auto &val : seq) cout << val << " ";
}