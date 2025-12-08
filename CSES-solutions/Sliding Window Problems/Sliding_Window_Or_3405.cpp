/* problem statement text */
/*
CSES - Sliding Window Or

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers. Your task is to calculate the bitwise or of each window of kkk elements, from left to right.
In this problem the input data is large and it is created using a generator.
Input
The first line contains two integers nnn and kkk: the number of elements and the size of the window.
The next line contains four integers xxx, aaa, bbb and ccc: the input generator parameters. The input is generated as follows:

x1=xx_1=xx1​=x
xi=(axi−1+b) mod cx_i=(ax_{i-1}+b) \bmod cxi​=(axi−1​+b)modc for i=2,3,…,ni=2,3,\dots,ni=2,3,…,n

Output
Print the xor of all window ors.
Constraints

1≤k≤n≤1071 \le k \le n \le 10^71≤k≤n≤107
0≤x,a,b≤1090 \le x, a, b \le 10^90≤x,a,b≤109
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
8 5
3 7 1 11

Output:
4

Explanation: The input array is [3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6][3,0,1,8,2,4,7,6]. The windows are [3,0,1,8,2][3,0,1,8,2][3,0,1,8,2], [0,1,8,2,4][0,1,8,2,4][0,1,8,2,4], [1,8,2,4,7][1,8,2,4,7][1,8,2,4,7] and [8,2,4,7,6][8,2,4,7,6][8,2,4,7,6], and their ors are 111111, 151515, 151515 and 151515. Thus, the answer is 11⊕15⊕15⊕15=411 \oplus 15 \oplus 15 \oplus 15 = 411⊕15⊕15⊕15=4.
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
 
/*
  A data structure that supports:
    - push_back(x): add element to the back
    - pop_front(): remove element from the front
    - get(): return aggregate of all current elements in O(1)
 
  Implemented using two MonoStacks, each storing prefix aggregates.
  Queue = [out (front)] ++ [in (back)], total = merge(out.get(), in.get()).
  Amortized O(1) per operation.
 
  merge must be associative & closed (identity optional, O(1) cost).
  Works for: sum, max, min, bitwise OR/AND/XOR, string concat, etc.
*/
 
template<typename T>
struct MonoStack {
    stack<pair<T, T> > st;
    function<T(T, T)> merge;
 
    MonoStack(function<T(T, T)> merge)
        : merge(merge) {
    }
 
    void push(T x) {
        T cur = st.empty() ? x : merge(x, st.top().second);
        st.push({x, cur});
    }
 
    void pop() { st.pop(); }
 
    size_t size() const { return st.size(); }
 
    bool empty() const { return st.empty(); }
 
    T top() const { return st.top().first; }
 
    T get() const { return st.top().second; }
};
 
template<typename T>
struct MonoQueue {
    MonoStack<T> in, out;
    function<T(T, T)> merge;
 
    MonoQueue(function<T(T, T)> merge)
        : merge(merge), in(merge), out(merge) {
    }
 
    void push(T x) { in.push(x); }
 
    void moveInToOut() {
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }
 
    void pop() {
        if (out.empty())
            moveInToOut();
        out.pop();
    }
 
    T front() {
        if (out.empty())
            moveInToOut();
        return out.top();
    }
 
    size_t size() const { return in.size() + out.size(); }
 
    bool empty() const { return in.empty() && out.empty(); }
 
    T get() const {
        if (in.empty())
            return out.get();
        if (out.empty())
            return in.get();
        return merge(out.get(), in.get()); // preserve queue order
    }
};
 
int lst[31];
 
int main() {
    PRE();
    int n, k;
    ll x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;
    ll ans = 0;
    vector<ll> v(n);
    v[0] = x;
    memset(lst, -1, sizeof lst);
    for (int i = 1; i < n; i++) {
        v[i] = (v[i - 1] * a + b) % c;
    }
    MonoQueue<ll> q([](ll a, ll b) -> ll {
        return a | b;
    });
    for (int i = 0; i < n; i++) {
        if (i >= k) {
            ans ^= q.get();
            q.pop();
        }
        q.push(v[i]);
    }
    ans ^= q.get();
    cout << ans << '\n';
}