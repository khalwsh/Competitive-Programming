/* problem statement text */
/*
CSES - Edit Distance

Time limit: 1.00 s
Memory limit: 512 MB

The edit distance between two strings is the minimum number of operations required to transform one string into the other.
The allowed operations are:

Add one character to the string.
Remove one character from the string.
Replace one character in the string.

For example, the edit distance between LOVE and MOVIE is 2, because you can first replace L with M, and then add I.
Your task is to calculate the edit distance between two strings.
Input
The first input line has a string that contains nnn characters between A–Z.
The second input line has a string that contains mmm characters between A–Z.
Output
Print one integer: the edit distance between the strings.
Constraints

1≤n,m≤50001 \le n,m \le 50001≤n,m≤5000

Example
Input:
LOVE
MOVIE

Output:
2
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5001;
int dp[N][N];
string s , t;
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    memset(dp , '?' , sizeof dp);
    cin>>s>>t;
    if(s.size() > t.size())swap(s , t);
    int n = s.size() , m = t.size();
    for(int i=0;i<=m;i++){
        dp[0][i] = i;
    }
    for(int i=0;i<=n;i++){
        dp[i][0] = i;
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            if(s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            dp[i][j] = min(dp[i][j] , 1 + dp[i - 1][j]);
            dp[i][j] = min(dp[i][j] , 1 + dp[i][j - 1]);
            dp[i][j] = min(dp[i][j] , 1 + dp[i - 1][j - 1]);
        }
    }
    cout<<dp[n][m];
}