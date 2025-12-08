/* problem statement text */
/*
CSES - Colored Chairs

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn chairs arranged in a circle. Each chair is either red or blue. The chairs are numbered 1,2,…,n1, 2,\dots, n1,2,…,n; chairs iii and i+1i+1i+1 are next to each other for all 1≤i≤n1 \le i \le n1≤i≤n. Here chair n+1n+1n+1 refers to chair 111.
Your task is to find two chairs that have the same color and are next to each other.
To do this, you can ask questions: you can choose a chair and you will be told the color of that chair.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You should start by reading a single integer nnn: the number of chairs.
On your turn, you can print one of the following:

"? i?\ i? i", where 1≤i≤n1 \le i \le n1≤i≤n: ask the color of chair iii. The grader will return R or B for red or blue.
"! i!\ i! i": report that chairs iii and i+1i+1i+1 have the same color. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.
Constraints

3≤n≤2⋅1053 \le n \le 2 \cdot 10^53≤n≤2⋅105, nnn is odd
you can ask at most 202020 questions of type ???

Example5
? 1
R
? 2
B
? 3
B
! 2
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
int ask(int i) {
    cout << "? " << i << endl;
    char x;cin >> x;
    return x == 'R';
}
void answer(int x) {
    cout << "! " << x << endl;
    exit(0);
}
int main() {
    // PRE();
    int n;cin >> n;
    int v1 = ask(1) , v2 = ask(n);
    if (v1 == v2) {
        answer(n);
    }
    int left = 1 , right = n;
    int res = 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int x = ask(mid);
        int len1 = mid  , len2 = n - mid + 1;
        if ((len1 & 1 ^ 1) && x == v1 || x != v1 && (len1 & 1)) {
            // go left
            right = mid - 1;
            res = mid - 1;
        }else {
            left = mid + 1;
            res = mid;
        }
    }
    answer(res);
}