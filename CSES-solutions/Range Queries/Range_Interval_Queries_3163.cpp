/* problem statement text */
/*
CSES - Range Interval Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array xxx of nnn integers, your task is to process qqq queries of the form: how many integers iii satisfy a≤i≤ba \le i \le ba≤i≤b and c≤xi≤dc \le x_i \le dc≤xi​≤d?
Input
The first line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has four integers aaa, bbb, ccc and ddd: how many integers iii satisfy a≤i≤ba \le i \le ba≤i≤b and c≤xi≤dc \le x_i \le dc≤xi​≤d?
Output
Print the result of each query.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n
1≤c≤d≤1091 \le c \le d \le 10^91≤c≤d≤109

Example
Input:
8 4
3 2 4 5 1 1 5 3
2 4 2 4
5 6 2 9
1 8 1 5
3 3 4 4

Output:
2
0
8
1
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
 
struct Node {
    int sum = 0;
    Node *left , *right;
    Node(int x) {
        sum = x;
        left = right = nullptr;
    }
    Node (Node *left ,Node *right) {
        this->left = left , this->right = right;
        if (left) sum += left->sum;
        if (right) sum += right -> sum;
    }
};
 
int get_sum(Node *p) {
    return (p == nullptr ? 0 : p->sum);
}
Node *Left(Node *p) {
    return (p == nullptr ? nullptr : p->left);
}
Node *Right(Node *p) {
    return (p == nullptr ? nullptr : p->right);
}
 
Node* upd(int nl , int nr , Node *version , int pos , int delta) {
    if (nl == nr && nl == pos) {
        return new Node(delta + get_sum(version));
    }
    int mid = nl + (nr - nl) / 2;
    if (pos <= mid) return new Node (upd(nl , mid , Left(version) , pos , delta) , Right(version));
    else return new Node(Left(version) , upd(mid + 1 , nr , Right(version) , pos , delta));
}
int qry(int nl , int nr , Node *version , Node *version2 , int x , int y) {
    if (!version) return 0;
    if (nl >= x && nr <= y) return get_sum(version) - get_sum(version2);
    if (nl > y || nr < x) return 0;
    int mid = nl + (nr - nl) / 2;
    return qry(nl , mid , Left(version) , Left(version2), x , y) + qry(mid + 1 ,nr ,Right(version) , Right(version2) , x , y);
}
 
const int N = 2e5 + 10;
Node *roots[N];
int main() {
    PRE();
    int n , q;cin >> n >> q;
    vector<int>v(n + 1) , all;
    for (int i = 1;i <= n;i++) cin >> v[i] , all.emplace_back(v[i]);
    sort(all.begin() , all.end());
    all.erase(unique(all.begin() , all.end()) , all.end());
    for (int i = 1;i <= n;i++) v[i] = lower_bound(all.begin() , all.end() , v[i]) - all.begin();
    roots[0] = nullptr;
    for (int i = 1;i <= n;i++) {
        roots[i] = upd(0 , N - 1 , roots[i - 1] , v[i] , 1);
    }
    for (int i = 0;i < q;i++) {
        int a , b , c , d; cin >> a >> b >> c >> d;
        cout << qry(0 , N - 1 , roots[b] , roots[a - 1], lower_bound(all.begin() , all.end() , c) - all.begin()
            , upper_bound(all.begin() , all.end() , d) - all.begin() - 1) << '\n';
    }
}