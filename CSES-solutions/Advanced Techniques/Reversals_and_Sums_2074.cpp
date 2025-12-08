/* problem statement text */
/*
CSES - Reversals and Sums

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, you have to process following operations:

reverse a subarray
calculate the sum of values in a subarray

Input
The first input line has two integers nnn and mmm: the size of the array and the number of operations. The array elements are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The next line as nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Finally, there are mmm lines that describe the operations. Each line has three integers ttt, aaa and bbb. If t=1t=1t=1, you should reverse a subarray from aaa to bbb. If t=2t=2t=2, you should calculate the sum of values from aaa to bbb.
Output
Print the answer to each operation where t=2t=2t=2.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤m≤1051 \le m \le 10^51≤m≤105
0≤xi≤1090 \le x_i \le 10^90≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 3
2 1 3 4 5 3 4 4
2 2 4
1 3 6
2 2 4

Output:
8
9
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
    ll val;
    bool rev;
    ll sum = 0;
    Treap *kids[2];
    Treap(ll k = 0) {
        sum = val = k;
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
    me -> sum = me -> val;
    for (auto child : me->kids) if (child) me -> size += child -> size , me -> sum += child -> sum;
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
 
int main() {
    PRE();
    int n , q;cin >> n >> q;
    vector<ll>v(n);for (auto &val : v) cin >> val;
    Treap* root = new Treap(v[0]);
    for (int i = 1;i  < n;i++) {
        root = Merge(root , new Treap(v[i]));
    }
    while (q--) {
        int typ;cin >>typ;
        int l , r;cin >> l >> r;
        l-- , r--;
        if (typ == 1){
            auto [p1 , rest] = split(root , l);
            auto [p2 , p3] = split(rest , r - l + 1);
            if (p2) p2 -> rev ^= true , prop(p2) , recalc(p2);
            root = Merge(p1 , Merge(p2 , p3));
        }else {
            auto [p1 , rest] = split(root , l);
            auto [p2 , p3] = split(rest , r - l + 1);
            cout << p2 -> sum << '\n';
            root = Merge(p1 , Merge(p2 , p3));
        }
    }
}