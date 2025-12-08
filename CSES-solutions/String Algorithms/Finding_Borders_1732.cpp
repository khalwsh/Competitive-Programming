/* problem statement text */
/*
CSES - Finding Borders

Time limit: 1.00 s
Memory limit: 512 MB

A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.
Your task is to find all border lengths of a given string.
Input
The only input line has a string of length nnn consisting of characters a–z.
Output
Print all border lengths of the string in increasing order.
Constraints

1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
abcababcab

Output:
2 5
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
 
long long randomLongLong(long long l, long long r) {
    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}
 
const int mod1 = 1e9 + 9;
const int mod2 = 1e9 + 21;
const int base1 = randomLongLong(23 , 435);
const int base2 = randomLongLong(23 , 435);
const int N = 1e6 + 10;
 
ll powers1[N] , powers2[N];
int main() {
    PRE();
    powers1[0] = 1;
    powers2[0] = 1;
    for(int i = 1;i < N;i++)powers1[i] = powers1[i  - 1] * base1 % mod1;
    for(int i = 1;i < N;i++)powers2[i] = powers2[i  - 1] * base2 % mod2;
    string s;cin>>s;
 
    unordered_map<ll , ll>hashes;
    ll reverse_hash1 = 0 , reverse_hash2 = 0;
    for(int i = s.size() - 1;i >= 0;i--) {
        reverse_hash1 += powers1[s.size() - i - 1] * s[i];
        reverse_hash2 += powers2[s.size() - i - 1] * s[i];
        reverse_hash1 %= mod1;
        reverse_hash2 %= mod2;
        hashes[reverse_hash1] = reverse_hash2;
    }
    ll cur_hash1 = 0;
    ll cur_hash2 = 0;
    for(int i = 0;i + 1 < s.size();++i) {
        cur_hash1 = cur_hash1 * base1 + s[i];
        cur_hash2 = cur_hash2 * base2 + s[i];
        cur_hash1 %= mod1;
        cur_hash2 %= mod2;
        if(hashes.count(cur_hash1) && hashes[cur_hash1] == cur_hash2)cout<<i + 1<<" ";
    }
}