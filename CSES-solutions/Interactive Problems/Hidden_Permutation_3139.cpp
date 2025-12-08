/* problem statement text */
/*
CSES - Hidden Permutation

Time limit: 1.00 s
Memory limit: 512 MB

There is a hidden permutation a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​ of integers 1,2,…,n1, 2,\dots, n1,2,…,n. Your task is to find this permutation.
To do this, you can ask questions: you can choose two indices iii and jjj and you will be told if ai<aja_i < a_jai​<aj​.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer nnn: the length of the permutation.
On your turn, you can print one of the following:

"? i j?\ i\ j? i j", where 1≤i,j≤n1 \le i, j \le n1≤i,j≤n: ask if ai<aja_i < a_jai​<aj​. The grader will return YES if ai<aja_i < a_jai​<aj​ and NO otherwise.
"! a1 a2…an!\ a_1\ a_2 \dots a_n! a1​ a2​…an​": report that the hidden permutation is a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
you can ask at most 10410^4104 questions of type ???

Example3
? 3 2
NO
? 3 1
YES
! 3 1 2

Explanation: The hidden permutation is [3,1,2][3, 1, 2][3,1,2]. The first question asks if a3<a2a_3 < a_2a3​<a2​ which is false, so the answer is NO. The second question asks if a3<a1a_3 < a_1a3​<a1​ which is true, so the answer is YES.
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
const int N = 1e3 + 1;
int res[N];
int ask(int i , int j) {
    cout << "? " << i << " " << j << endl;
    string x;cin >> x;
    return x[0] == 'Y' ? 1 : 0;
}
pair<int , int> ind[N];
void solve(int l , int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    solve(l , mid);
    solve(mid + 1 , r);
    int i = l , j = mid + 1;
    vector<pair<int , int>> ord;
    while (i <= mid && j <= r) {
        int x = ask(ind[i].first , ind[j].first);
        if (x) {
            ord.emplace_back(ind[i]) , i++;
            res[ind[i - 1].second] += (r - j + 1);
        }else {
            ord.emplace_back(ind[j]) , j++;
            res[ind[j - 1].second] += (mid - i + 1);
        }
    }
    while (i <= mid) ord.emplace_back(ind[i++]);
    while (j <= r) ord.emplace_back(ind[j++]);
    for (i = l; i <= r;i++) {
        ind[i] = ord[i - l];
    }
}
int main() {
    // PRE();
    int n;
    cin >> n;
    for (int i = 1;i <= n;i++) ind[i] = {i , i};
    solve(1 , n);
    // assert(count(res + 1 , res + n + 1 , 0) == 0);
    cout << "! ";
    for (int i = 1;i <= n;i++) cout << n - res[i] << " ";
    cout << endl;
}