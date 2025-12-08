/* problem statement text */
/*
CSES - Range Queries and Copies

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to maintain a list of arrays which initially has a single array. You have to process the following types of queries:

Set the value aaa in array kkk to xxx.
Calculate the sum of values in range [a,b][a,b][a,b] in array kkk.
Create a copy of array kkk and add it to the end of the list.

Input
The first input line has two integers nnn and qqq: the array size and the number of queries.
The next line has nnn integers t1,t2,…,tnt_1,t_2,\ldots,t_nt1​,t2​,…,tn​: the initial contents of the array.
Finally, there are qqq lines describing the queries. The format of each line is one of the following: "1 kkk aaa xxx", "2 kkk aaa bbb" or "3 kkk".
Output
Print the answer to each sum query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤ti,x≤1091 \le t_i, x \le 10^91≤ti​,x≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 6
2 3 1 2 5
3 1
2 1 1 5
2 2 1 5
1 2 2 5
2 1 1 5
2 2 1 5

Output:
13
13
13
15
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
int n , q;
const int N = 2e5 + 10;
int a[N];
struct Node {
    ll sum = 0;
    Node *left , *right;
    Node(ll nw): sum(nw){}
    Node(Node* L = nullptr , Node *R = nullptr) {
        left = L , right = R;
        sum = 0;
        if (L) sum += L->sum;
        if (R) sum += R->sum;
    }
};
Node *roots[N];
Node* build(int l , int r) {
    if (l == r) {
        return new Node(a[l]);
    }
    int mid = l + (r - l) / 2;
    return new Node(build(l , mid),build(mid + 1 , r));
}
Node* upd(int l , int r , int i , int nw, Node *version) {
    if (l == r) return new Node(nw);
    int mid = l + (r - l) / 2;
    if (i <= mid) {
        return new Node(upd(l , mid , i , nw , version->left) , version->right);
    }else {
        return new Node(version->left , upd(mid + 1 , r , i , nw , version->right));
    }
}
ll query(int l , int r , int i , int j , Node *version) {
    if (l >= i && r <= j)return version->sum;
    if (r < i || l > j)return 0;
    int mid = l + (r - l) / 2;
    return query(l , mid , i , j , version->left) + query(mid + 1 , r , i , j , version->right);
}
int main() {
    PRE();
    cin>>n>>q;
    for (int i = 0;i < n;i++) {
        cin>>a[i];
    }
    int idx = 1;
    roots[0] = build(0 , n - 1);
    while (q--) {
        int type;cin>>type;
        if (type == 1) {
            int k , A , x;cin>>k>>A>>x;
            roots[k - 1] = upd(0 , n - 1 , A - 1 , x , roots[k - 1]);
        }else if (type == 2) {
            int k , A , B;cin>>k>>A>>B;
            cout<<query(0 , n - 1 , A - 1 , B - 1 , roots[k - 1])<<'\n';
        }else {
            int k;cin>>k;
            roots[idx++] = roots[k - 1];
        }
    }
}