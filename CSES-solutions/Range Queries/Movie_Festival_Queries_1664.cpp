/* problem statement text */
/*
CSES - Movie Festival Queries

Time limit: 1.00 s
Memory limit: 512 MB

In a movie festival, nnn movies will be shown. You know the starting and ending time of each movie.
Your task is to process qqq queries of the form: if you arrive and leave the festival at specific times, what is the maximum number of movies you can watch?
You can watch two movies if the first movie ends before or exactly when the second movie starts. You can start the first movie exactly when you arrive and leave exactly when the last movie ends.
Input
The first input line has two integers nnn and qqq: the number of movies and queries.
After this, there are nnn lines describing the movies. Each line has two integers aaa and bbb: the starting and ending time of a movie.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb: your arrival and leaving time.
Output
Print the maximum number of movies for each query.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤a<b≤1061 \le a < b \le 10^61≤a<b≤106

Example
Input:
4 3
2 5
6 10
4 7
9 10
5 9
2 10
7 10

Output:
0
2
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
const int N = 1e6 + 10 , K = 20;
int up[N][K];
int main() {
    PRE();
    int n , q; cin >> n >> q;
    vector<pair<int , int>> v(n);
    for (int i = 0;i < n;i++) cin >> v[i].first >> v[i].second;
    sort(v.begin() , v.end());
 
    for (int i = 0;i < N;i++)
        for (int j = 0;j < K;j++)
            up[i][j] = N - 1;
 
    for (int i = n - 2;i >= 0;i--)
        v[i].second = min(v[i].second , v[i + 1].second);
 
    int k = 0;
    for (int i = 0;i < N;i++) {
        while (k < v.size() && v[k].first < i)k++;
        up[i][0] = (k == v.size() ? N - 1 : v[k].second);
        // if (i <= 10) cout << i << " " << up[i][0] << endl;
    }
 
    for (int i = 1;i < K;i++) {
        for (int j = 0;j < N;j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
    while (q--) {
        int l , r; cin >> l >> r;
        int ans = 0;
        for (int i = K - 1;i >= 0;i--) {
            // cout << l << " " << up[l][i] << endl;
            if (up[l][i] <= r) {
                l = up[l][i];
                ans += 1 << i;
            }
        }
        cout << ans << '\n';
    }
}