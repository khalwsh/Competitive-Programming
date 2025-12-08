/* problem statement text */
/*
CSES - Task Assignment

Time limit: 1.00 s
Memory limit: 512 MB

A company has nnn employees and there are nnn tasks that need to be done. We know for each employee the cost of carrying out each task. Every employee should be assigned to exactly one task. What is the minimum total cost if we assign the tasks optimally and how could they be assigned?
Input
The first input line has one integer nnn: the number of employees and the number of tasks that need to be done.
After this, there are nnn lines each consisting of nnn integers. The iiith line consists of integers ci1,ci2,…,cinc_{i1},c_{i2},\ldots,c_{in}ci1​,ci2​,…,cin​: the cost of each task when it is assigned to the iiith employee.
Output
First print the minimum total cost.
Then print nnn lines each consisting of two integers aaa and bbb: you assign the bbbth task to the aaath employee.
If there are multiple solutions you can print any of them.
Constraints

1≤n≤2001 \le n \le 2001≤n≤200
1≤cij≤10001 \le c_{ij} \le 10001≤cij​≤1000

Example
Input:
4
17 8 16 9
7 15 12 19
6 9 10 11
14 7 13 10

Output:
33
1 4
2 1
3 3
4 2

Explanation: The minimum total cost is 333333. We can reach this by assigning employee 1 task 4, employee 2 task 1, employee 3 task 3 and employee 4 task 2. This will cost 9+7+10+7=339 + 7 + 10 + 7 = 339+7+10+7=33.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int INF = 1000 * 1000 * 1000;
pair<int, vector<pair<int, int>>> hungarianAlgorithm(const vector<vector<int>>& cost) {
    int n = cost.size();
    vector<int> u(n + 1, 0), v(n + 1, 0), p(n + 1, 0), way(n + 1, 0);
 
    for (int i = 1; i <= n; i++) {
        vector<int> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        int j0 = 0;
        p[0] = i;
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
 
    vector<pair<int, int>> assignment;
    for (int j = 1; j <= n; j++) {
        if (p[j]) {
            assignment.emplace_back(p[j], j);
        }
    }
    return {-v[0], assignment};
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<vector<int>>a(n , vector<int>(n));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++)
            cin>>a[i][j];
    }
    auto res = hungarianAlgorithm(a);
    cout<<res.first<<'\n';
    for(auto &val:res.second) {
        cout<<val.first<<" "<<val.second<<'\n';
    }
}