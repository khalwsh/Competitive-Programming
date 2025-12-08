/* problem statement text */
/*
CSES - Course Schedule II

Time limit: 1.00 s
Memory limit: 512 MB

You want to complete nnn courses that have requirements of the form "course aaa has to be completed before course bbb".
You want to complete course 111 as soon as possible. If there are several ways to do this, you want then to complete course 222 as soon as possible, and so on.
Your task is to determine the order in which you complete the courses.
Input
The first input line has two integers nnn and mmm: the number of courses and requirements. The courses are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the requirements. Each line has two integers aaa and bbb: course aaa has to be completed before course bbb.
You can assume that there is at least one valid schedule.
Output
Print one line having nnn integers: the order in which you complete the courses.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 2
2 1
2 3

Output:
2 1 3 4
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
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
 
    vector<int> in(n + 1);
    vector<vector<int>> radj(n + 1);
 
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        radj[b].push_back(a);
        in[a]++;
    }
    priority_queue<int> pq;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) { pq.push(i); }
    }
 
    vector<int> ans;
    while (pq.size()) {
        int x = pq.top();
        pq.pop();
        ans.push_back(x);
 
        for (int t : radj[x]) {
            in[t]--;
            if (!in[t]) { pq.push(t); }
        }
    }
    reverse(ans.begin(), ans.end());
    for (int t : ans) { cout << t << " "; }
}