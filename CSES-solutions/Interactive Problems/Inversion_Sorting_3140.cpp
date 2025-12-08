/* problem statement text */
/*
CSES - Inversion Sorting

Time limit: 1.00 s
Memory limit: 512 MB

There is a hidden permutation a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​ of integers 1,2,…,n1, 2,\dots, n1,2,…,n. Your task is to sort the permutation by reversing subarrays.
On each turn, you can reverse a subarray of the permutation. After that, you will be reported the number of inversions in the permutation. If the number of inversions is 000 (i.e., the permutation is sorted), you win.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer nnn: the length of the permutation.
On your turn, print two integers iii and jjj: reverse the subarray between indices iii and jjj.
After this, the next input line has a single integer: the number of inversions after the operation. If the number is 000, you win and your program must terminate after this.
Constraints

1≤n≤10001\leq n\leq 10001≤n≤1000
you can make at most 4n4n4n operations

Example3
1 2
1
2 3
0

Explanation: Here the initial permutation is [3,1,2][3,1,2][3,1,2]. After the first operation the permutation is [1,3,2][1,3,2][1,3,2] and the number of inversions is 111. After the second operation the permutation is [1,2,3][1,2,3][1,2,3] and the number of inversions is 000.
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
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int n=0): n(n), f(n+1,0) {}
    void add(int i,int delta){
        for(; i<=n; i += i&-i) f[i]+=delta;
    }
    int sum(int i){
        int s=0;
        for(; i>0; i-=i&-i) s+=f[i];
        return s;
    }
    int find_kth(int k){
        int idx=0;
        int bit = 1;
        while(bit<<1 <= n) bit <<= 1;
        for(; bit>0; bit >>= 1){
            int nxt = idx + bit;
            if(nxt <= n && f[nxt] < k){
                idx = nxt;
                k -= f[nxt];
            }
        }
        return idx+1;
    }
};
 
int main() {
    // PRE();
    int n;
    cin >> n;
 
    vector<ll> inv(n+1,0);
    for(int i=1;i<=n;i++){
        cout << 1 << " " << i << "\n" << flush;
        ll cur;
        cin >> cur;
        cout << 1 << " " << i << "\n" << flush;
        ll pre;
        cin >> pre;
        ll C2 = 1LL * i * (i-1) / 2;
        ll delta = cur - pre;
        ll invi = (C2 - delta) / 2;
        inv[i] = invi;
    }
 
    vector<ll> b(n+1,0);
    for(int i=1;i<=n;i++) b[i] = inv[i] - inv[i-1];
    Fenwick bit(n);
    for(int x=1;x<=n;x++) bit.add(x,1);
    vector<int> a(n+1,0);
    for(int i=n;i>=1;i--){
        int k = int(i - b[i]);
        int val = bit.find_kth(k);
        a[i] = val;
        bit.add(val, -1);
    }
 
    for(int t=1; t<=n; t++){
        int pos = -1;
        for(int j=t;j<=n;j++){
            if(a[j] == t){ pos = j; break; }
        }
        if(pos == -1) continue;
        if(pos == t) continue;
        cout << t << " " << pos << "\n" << flush;
        ll new_inv;
        cin >> new_inv;
        reverse(a.begin() + t, a.begin() + pos + 1);
        if(new_inv == 0) return 0;
    }
}