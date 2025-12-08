/* problem statement text */
/*
CSES - Movie Festival

Time limit: 1.00 s
Memory limit: 512 MB

In a movie festival nnn movies will be shown. You know the starting and ending time of each movie. What is the maximum number of movies you can watch entirely?
Input
The first input line has an integer nnn: the number of movies.
After this, there are nnn lines that describe the movies. Each line has two integers aaa and bbb: the starting and ending times of a movie.
Output
Print one integer: the maximum number of movies.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a<b≤1091 \le a < b \le 10^91≤a<b≤109

Example
Input:
3
3 5
4 9
5 8

Output:
2
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 3;
int n;
pair<int , int>tasks[N];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    cin>>n;
    for(int i = 0;i < n;i++)cin>>tasks[i].first>>tasks[i].second;
    sort(tasks , tasks + n , [&](pair<int , int>&a , pair<int , int>&b)->bool {
       return a.second < b.second;
    });
    int res = 0;
    int t = -1;
    for(int i = 0;i < n;i++) {
        if(tasks[i].first >= t)t = tasks[i].second , res++;
    }
    cout<<res<<'\n';
}