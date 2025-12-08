/* problem statement text */
/*
CSES - Hidden Integer

Time limit: 1.00 s
Memory limit: 512 MB

There is a hidden integer xxx. Your task is to find the value of xxx.
To do this, you can ask questions: you can choose an integer yyy and you will be told if y<xy < xy<x.
Interaction
This is an interactive problem. Your code will interact with the grader using standard input and output. You can start asking questions right away.
On your turn, you can print one of the following:

"? y?\ y? y", where 1≤y≤1091 \le y \le 10^91≤y≤109: ask if y<xy < xy<x. The grader will return YES if y<xy < xy<x and NO otherwise.
"! x!\ x! x": report that the hidden integer is xxx. Your program must terminate after this.

Each line should be followed by a line break. You must make sure the output gets flushed after printing each line.
Constraints

1≤x≤1091 \le x \le 10^91≤x≤109
you can ask at most 303030 questions of type ???

Example? 3
YES
? 6
YES
? 7
NO
! 7
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
string ask(int mid) {
    cout << "? " << mid << endl;
    string s; cin >> s;
    return s;
}
void answer(int res) {
    cout << "! " << res;
}
int main() {
    // PRE();
    int cnt = 30;
    int left = 1 , right = 1e9;
    int res = 1;
    while (cnt--) {
        int mid = left + (right - left) / 2;
        if (ask(mid)[0] == 'Y') {
            left = mid + 1;
            res = mid + 1;
        }else
            right = mid - 1;
    }
    answer(res);
}