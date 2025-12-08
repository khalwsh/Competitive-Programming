/* problem statement text */
/*
CSES - Book Shop

Time limit: 1.00 s
Memory limit: 512 MB

You are in a book shop which sells nnn different books. You know the price and number of pages of each book.
You have decided that the total price of your purchases will be at most xxx. What is the maximum number of pages you can buy? You can buy each book at most once.
Input
The first input line contains two integers nnn and xxx: the number of books and the maximum total price.
The next line contains nnn integers h1,h2,…,hnh_1,h_2,\ldots,h_nh1​,h2​,…,hn​: the price of each book.
The last line contains nnn integers s1,s2,…,sns_1,s_2,\ldots,s_ns1​,s2​,…,sn​: the number of pages of each book.
Output
Print one integer: the maximum number of pages.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
1≤x≤1051 \le x \le 10^51≤x≤105
1≤hi,si≤10001 \le h_i, s_i \le 10001≤hi​,si​≤1000

Example
Input:
4 10
4 8 5 3
5 12 8 1

Output:
13

Explanation: You can buy books 1 and 3. Their price is 4+5=94+5=94+5=9 and the number of pages is 5+8=135+8=135+8=13.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7 , N = 1e5 + 1;
int h[N] , p[N];
int n;
vector<int> dp[2]; // max number of pages you can buy with i coins
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    cin>>n;
    int x;cin>>x;
    for(int i = 0;i < n;i++)cin>>h[i];
    for(int i = 0;i < n;i++)cin>>p[i];
    dp[0] = vector<int>(x + 1);
    dp[1] = vector<int>(x + 1);
    dp[0][0] = 0;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j <= x;j++)dp[1][j] = dp[0][j];
        for(int j = h[i];j <= x;j++) {
            dp[1][j] = max(dp[1][j] , dp[0][j - h[i]] + p[i]);
        }
        swap(dp[0] , dp[1]);
    }
    cout<<dp[0][x]<<'\n';
}