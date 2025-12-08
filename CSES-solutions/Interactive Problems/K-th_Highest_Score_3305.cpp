/* problem statement text */
/*
CSES - K-th Highest Score

Time limit: 1.00 s
Memory limit: 512 MB

There were nnn coders from Finland and nnn coders from Sweden in a programming contest. It turned out that after the contest, each coder had a distinct score.
Your task is to find the kkk-th highest score in the contest.
To do this, you can ask questions: you can choose a country (Finland or Sweden) and an integer iii and you will be told the iii-th highest score for the chosen country.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading two integers nnn and kkk.
On your turn, you can print one of the following:

"F i\mathrm{F}\ iF i", where 1≤i≤n1 \le i \le n1≤i≤n: ask the iii-th highest score for Finland.
"S i\mathrm{S}\ iS i", where 1≤i≤n1 \le i \le n1≤i≤n: ask the iii-th highest score for Sweden.
"! s!\ s! s": report that the kkk-th highest score is sss. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤k≤2n1 \le k \le 2n1≤k≤2n
each score is between 111 and 10910^9109
you can ask at most 100100100 queries of the first two types in total

Example3 1
F 1
9
S 1
8
! 9

Explanation: The scores for Finland are [9,4,3][9, 4, 3][9,4,3] and the scores for Sweden are [8,6,1][8, 6, 1][8,6,1]. Since k=1k = 1k=1, the task is to find the highest score overall, which in this case is 999.
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
    int n, k;
    cin >> n >> k;
    vector<long long> F(n + 2, -1LL);
    vector<long long> S(n + 2, -1LL);
    auto getF = [&](int i) -> long long {
        if (F[i] != -1LL) return F[i];
        cout << "F " << i << "\n" << flush;
        long long x;
        cin >> x;
        F[i] = x;
        return x;
    };
    auto getS = [&](int i) -> long long {
        if (S[i] != -1LL) return S[i];
        cout << "S " << i << "\n" << flush;
        long long x;
        cin >> x;
        S[i] = x;
        return x;
    };
    int left = max(0, k - n);
    int right = min(k, n);
    long long ans = 0;
    while (left <= right) {
        int partA = left + (right - left) / 2;
        int partB = k - partA;
        long long l1 = (partA == 0 ? -2000000000000000000LL : -getF(partA));
        long long r1 = (partA == n ? 2000000000000000000LL : -getF(partA + 1));
        long long l2 = (partB == 0 ? -2000000000000000000LL : -getS(partB));
        long long r2 = (partB == n ? 2000000000000000000LL : -getS(partB + 1));
        if (l1 <= r2 && l2 <= r1) {
            ans = -max(l1, l2);
            break;
        } else if (l1 > r2) {
            right = partA - 1;
        } else {
            left = partA + 1;
        }
    }
    cout << "! " << ans << "\n" << flush;
    return 0;
}