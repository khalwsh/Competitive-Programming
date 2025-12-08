/* problem statement text */
/*
CSES - String Functions

Time limit: 1.00 s
Memory limit: 512 MB

We consider a string of nnn characters, indexed 1,2,…,n1,2,\dots,n1,2,…,n. Your task is to calculate all values of the following functions:

z(i)z(i)z(i) denotes the maximum length of a substring that begins at position iii and is a prefix of the string. In addition, z(1)=0z(1)=0z(1)=0.
π(i)\pi(i)π(i) denotes the maximum length of a substring that ends at position iii, is a prefix of the string, and whose length is at most i−1i-1i−1.

Note that the function zzz is used in the Z-algorithm, and the function π\piπ is used in the KMP algorithm.
Input
The only input line has a string of length nnn. Each character is between a–z.
Output
Print two lines: first the values of the zzz function, and then the values of the π\piπ function.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
abaabca

Output:
0 0 1 2 0 0 1
0 0 1 1 2 0 1
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> zFunction(const string &s) {
    //it computes for every index i starts at i what is the largest string is matching a prefix
    int n = (int)s.size();
    vector<int> z(n);
    int left = 0, right = 0;
    for(int i = 1; i < n; i++) {
        if(i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while(i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}
vector<int>prefixFunction(const string &s) {
    vector<int>failure(s.size());
    for(int i = 1;i < s.size();i++) {
        int j = failure[i - 1];
        while(j > 0 && s[j] != s[i])j = failure[j - 1];
        if(s[j] == s[i])j++;
        failure[i] = j;
    }
    return failure;
}
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;cin>>s;
    for(auto &val:zFunction(s))cout<<val<<" ";
    cout<<'\n';
    for(auto &val:prefixFunction(s))cout<<val<<" ";
}