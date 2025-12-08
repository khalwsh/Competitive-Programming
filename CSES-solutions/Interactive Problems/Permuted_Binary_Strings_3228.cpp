/* problem statement text */
/*
CSES - Permuted Binary Strings

Time limit: 1.00 s
Memory limit: 512 MB

There is a hidden permutation a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​ of integers 1,2,…,n1, 2,\dots, n1,2,…,n. Your task is to find this permutation.
To do this, you can ask questions: you can choose a binary string b1b2…bnb_1b_2\dots b_nb1​b2​…bn​ and you will receive the binary string ba1ba2…banb_{a_1}b_{a_2}\dots b_{a_n}ba1​​ba2​​…ban​​.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer nnn: the length of the permutation.
On your turn, you can print one of the following:

"? b1b2…bn?\ b_1b_2\dots b_n? b1​b2​…bn​", where bi∈{0,1}b_i\in\{0, 1\}bi​∈{0,1}: The grader will return the binary string ba1ba2…banb_{a_1}b_{a_2}\dots b_{a_n}ba1​​ba2​​…ban​​.
"! a1 a2…an!\ a_1\ a_2 \dots a_n! a1​ a2​…an​": report that the hidden permutation is a1,a2,…,ana_1, a_2,\dots, a_na1​,a2​,…,an​. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
you can ask at most 101010 questions of type ???

Example3
? 100
100
? 010
001
? 001
010
! 1 3 2

Explanation: The hidden permutation is [1,3,2][1, 3, 2][1,3,2]. In the first question b1b2b3=100b_1b_2b_3 = 100b1​b2​b3​=100 and the grader returns ba1ba2ba3=b1b3b2=100b_{a_1}b_{a_2}b_{a_3} = b_1b_3b_2 = 100ba1​​ba2​​ba3​​=b1​b3​b2​=100. In the second question b1b2b3=010b_1b_2b_3 = 010b1​b2​b3​=010 and the grader returns b1b3b2=001b_1b_3b_2 = 001b1​b3​b2​=001.
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
string ask(string &q) {
    cout << "? " << q << endl;
    string s;cin >> s;
    return s;
}
const int N = 1 << 10;
int res[N];
int main() {
    // PRE();
    int n;cin >> n;
    vector<string> to_ask;
    for (int i = 0;(1 << i) <= n;i++) {
        string s;
        for (int j = 1;j <= n;j++) {
            if (j >> i & 1) {
                s += '1';
            }else
                s += '0';
        }
        to_ask.emplace_back(s);
    }
    vector<string> ans;
    for (auto &val : to_ask) ans.emplace_back(ask(val));
    for (int i = 0;i < to_ask.size();i++) {
        for (int j = 0;j < ans[i].size();j++) {
            if (ans[i][j] == '1') {
                res[j + 1] |= (1 << i);
            }
        }
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}