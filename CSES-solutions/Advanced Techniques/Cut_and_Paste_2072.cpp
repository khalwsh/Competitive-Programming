/* problem statement text */
/*
CSES - Cut and Paste

Time limit: 1.00 s
Memory limit: 512 MB

Given a string, your task is to process operations where you cut a substring and paste it to the end of the string. What is the final string after all the operations?
Input
The first input line has two integers nnn and mmm: the length of the string and the number of operations. The characters of the string are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The next line has a string of length nnn that consists of characters A–Z.
Finally, there are mmm lines that describe the operations. Each line has two integers aaa and bbb: you cut a substring from position aaa to position bbb.
Output
Print the final string after all the operations.
Constraints

1≤n,m≤2⋅1051 \le n, m \le 2 \cdot 10^51≤n,m≤2⋅105
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
7 2
AYBABTU
3 5
3 5

Output:
AYABTUB
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
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
static std::mt19937_64 RNG(
    (unsigned) chrono::steady_clock::now().time_since_epoch().count()
);
long long randomLongLong(long long l, long long r) {
    std::uniform_int_distribution<long long> dist(l, r);
    return dist(RNG);
}
struct Treap {
    ll priority , size;
    char val;
    bool rev;
    Treap *kids[2];
    Treap(char k = 'a') {
        val = k;
        size = 1;
        rev = false;
        priority = randomLongLong(1 , 1e18);
        kids[0] = kids[1] = nullptr;
    }
    ~Treap() {
        delete kids[0];
        delete kids[1];
    }
};
void prop(Treap* me) {
    if (!me) return;
    if (me -> rev) {
        swap(me -> kids[0] , me -> kids[1]);
        me -> rev ^= true;
        for (auto &child : me -> kids) if (child) child -> rev ^= true;
    }
}
void recalc(Treap* me) {
    if (me == nullptr) return;
    me -> size = 1;
    for (auto child : me->kids) if (child) me -> size += child -> size;
}
ll Size(Treap *me) {
    if (me == nullptr) return  0;
    return me->size;
}
 
pair<Treap* , Treap*> split(Treap* me , int toLeft) {
    if (me == nullptr) return {nullptr , nullptr};
    prop(me);
    if (Size(me -> kids[0]) >= toLeft) {
        auto p = split(me -> kids[0] , toLeft);
        me -> kids[0] = p.second;
        recalc(me);
        return {p.first , me};
    }else {
        auto p = split(me -> kids[1] , toLeft - Size(me -> kids[0]) - 1);
        me -> kids[1] = p.first;
        recalc(me);
        return {me , p.second};
    }
}
 
Treap* Merge(Treap* left , Treap* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    prop(left);
    prop(right);
    if (left -> priority < right -> priority) {
        left -> kids[1] = Merge(left -> kids[1] , right);
        recalc(left);
        return left;
    }else {
        right -> kids[0] = Merge(left , right -> kids[0]);
        recalc(right);
        return right;
    }
}
void print(Treap* root) {
    if (!root) return;
    prop(root);
    print(root -> kids[0]);
    cout << root -> val;
    print(root -> kids[1]);
}
int main() {
    PRE();
    int n , q;cin >> n >> q;
    string s; cin >> s;
    Treap* root = new Treap(s[0]);
    for (int i = 1;i  < n;i++) {
        root = Merge(root , new Treap(s[i]));
    }
    while (q--) {
        int l , r;cin >> l >> r;
        l-- , r--;
        auto [p1 , rest] = split(root , l);
        auto [p2 , p3] = split(rest , r - l + 1);
        root = Merge(p1 , Merge(p3 , p2));
    }
    print(root);
}