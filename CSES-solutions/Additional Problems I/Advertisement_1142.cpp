/* problem statement text */
/*
CSES - Advertisement

Time limit: 1.00 s
Memory limit: 512 MB

A fence consists of nnn vertical boards. The width of each board is 1 and their heights may vary.
You want to attach a rectangular advertisement to the fence. What is the maximum area of such an advertisement?
Input
The first input line contains an integer nnn: the width of the fence.
After this, there are nnn integers k1,k2,…,knk_1,k_2,\ldots,k_nk1​,k2​,…,kn​: the height of each board.
Output
Print one integer: the maximum area of an advertisement.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ki≤1091 \le k_i \le 10^91≤ki​≤109

Example
Input:
8
4 1 5 3 3 2 4 1

Output:
10
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
vector<int> getNxtMin(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
 
vector<int> getPrevMin(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = arr.size() - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
 
vector<int> getNxtMax(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
 
vector<int> getPrevMax(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = arr.size() - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
int main() {
    PRE();
    int n;cin >> n;
    vector<int>a(n);
    for (auto &val : a) cin >> val;
    auto left = getPrevMin(a);
    auto right = getNxtMin(a);
    ll res = 0;
    for (int i = 0;i < n;i++) {
        int L = left[i] == -1 ? 0 : left[i] + 1;
        int R = right[i] == -1 ? n - 1 : right[i] - 1;
        res = max(res , 1LL * a[i] * (R - L + 1));
    }
    cout << res << '\n';
}