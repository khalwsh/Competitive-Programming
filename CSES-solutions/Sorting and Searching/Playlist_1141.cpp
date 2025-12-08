/* problem statement text */
/*
CSES - Playlist

Time limit: 1.00 s
Memory limit: 512 MB

You are given a playlist of a radio station since its establishment. The playlist has a total of nnn songs.
What is the longest sequence of successive songs where each song is unique?
Input
The first input line contains an integer nnn: the number of songs.
The next line has nnn integers k1,k2,…,knk_1,k_2,\ldots,k_nk1​,k2​,…,kn​: the id number of each song.
Output
Print the length of the longest sequence of unique songs.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ki≤1091 \le k_i \le 10^91≤ki​≤109

Example
Input:
8
1 2 1 3 2 7 4 2

Output:
5
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
const int N = 3e5 + 10;
int v[N];
int n;
int main() {
    PRE();
    cin>>n;
    for(int i = 0;i < n;i++) {
        cin>>v[i];
    }
    int l = 0 , r = 0 , mx = 1;
    map<int , int>mp;
    while(r < n) {
        mp[v[r]]++;
        while(mp[v[r]] > 1) {
            mp[v[l]]--;
            ++l;
        }
        mx = max(mx , r - l + 1);
        r++;
    }
    cout<<mx<<'\n';
}