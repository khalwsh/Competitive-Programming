/* problem statement text */
/*
CSES - Forest Queries II

Time limit: 1.00 s
Memory limit: 512 MB

You are given an n×nn \times nn×n grid representing the map of a forest. Each square is either empty or has a tree. Your task is to process qqq queries of the following types:

Change the state (empty/tree) of a square.
How many trees are inside a rectangle in the forest?

Input
The first input line has two integers nnn and qqq: the size of the forest and the number of queries.
Then, there are nnn lines describing the forest. Each line has nnn characters: . is an empty square and * is a tree.
Finally, there are qqq lines describing the queries. The format of each line is either "111 yyy xxx" or "2 y1y_1y1​ x1x_1x1​ y2y_2y2​ x2x_2x2​".
Output
Print the answer to each query of the second type.
Constraints

1≤n≤10001 \le n \le 10001≤n≤1000
1≤q≤2⋅1051 \le q \le 2 \cdot 10^51≤q≤2⋅105
1≤y,x≤n1 \le y,x \le n1≤y,x≤n
1≤y1≤y2≤n1 \le y_1 \le y_2 \le n1≤y1​≤y2​≤n
1≤x1≤x2≤n1 \le x_1 \le x_2 \le n1≤x1​≤x2​≤n

Example
Input:
4 3
.*..
*.**
**..
****
2 2 2 3 4
1 3 3
2 2 2 3 4

Output:
3
4
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
// #define int long long
#define line '\n'
typedef long long ll;
typedef long double ld;
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
ll SafeMul(ll a,ll b,ll m){if(b==0)return 0;ll res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 4e5 + 5;
const int mod = 1e9 + 7;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
/*
    2D segment Tree
    - Memory allocation: O(4n x 4m)
    - range [l..r] , r: inclusive
    - Base: 0-index
 
    Function description:
        1. upd(r , c , val): update cell (r,c) with value val
           Time complexity: O(log(n) x log(m))
        2. qry(lx , rx , ly , ry): find (min,max,sum,produc) of rectangle [lx...rx] x [ly...ry]
           Time complexity: O(log(n) x log(m))
        3. init(n , m): initial the segment tree
        4. build(g): build the segment tree with grid[n][m]
           Time complexity: O(n log(n) x m log(m))
*/
struct Node{
    int v;
    Node(){ v = 0;}
    Node(ll x){ this->v = x; }
    Node operator +(const Node &other) const{
        Node res;
        res.v = v + other.v; // custom operator
        return res;
    }
};
struct segTree_2d{
private:
    vector<vector<Node>> t;
    int n , m;
    void build_y(int vx, int lx, vector<vector<int>> &g ,int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx){
                t[vx][vy] = Node(g[lx][ly]);
            }
            else{
                t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
            }
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, g, rx, vy*2, ly, my);
            build_y(vx, lx, g, rx, vy*2+1, my+1, ry);
            t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
        }
    }
    void build_x(vector<vector<int>> &g , int vx, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(g , vx*2, lx, mx);
            build_x(g , vx*2+1, mx+1, rx);
        }
        build_y(vx, lx, g, rx, 1, 0, m-1);
    }
    Node qry_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry)
            return Node();
        if (ly == tly && try_ == ry)
            return Node(t[vx][vy]);
        int tmy = (tly + try_) / 2;
        return qry_y(vx, vy*2, tly, tmy, ly, min(ry, tmy)) +
               qry_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
    }
 
    Node qry_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return Node();
        if (lx == tlx && trx == rx)
            return qry_y(vx, 1, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return qry_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry) +
               qry_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
    }
    void upd_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int nval) {
        if (ly == ry) {
            if (lx == rx)
                t[vx][vy] = nval;
            else
                t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            if (y <= my)
                upd_y(vx, lx, rx, vy*2, ly, my, x, y, nval);
            else
                upd_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, nval);
            t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
        }
    }
    void upd_x(int vx, int lx, int rx, int x, int y, int nval) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                upd_x(vx*2, lx, mx, x, y, nval);
            else
                upd_x(vx*2+1, mx+1, rx, x, y, nval);
        }
        upd_y(vx, lx, rx, 1, 0, m-1, x, y, nval);
    }
public:
    void init(int n, int m){
        this->n = n;
        this->m = m;
        int r = 1 , c = 1;
        while(r < n) r *= 2;
        while(c < m) c *= 2;
        t = vector<vector<Node>>(2 * r , vector<Node>(2 * c));
    }
    void build(vector<vector<int>> &g){
        build_x(g , 1 , 0 , n - 1);
    }
    int qry(int x , int y , int xx , int yy){
        return qry_x(1 , 0 , n - 1 , x , xx , y , yy).v;
    }
    void upd(int r , int c , int val){
        // set
        upd_x(1 , 0 , n - 1 , r , c , val);
    }
};
int main() {
    khaled
    segTree_2d seg;
    int n;cin>>n;
    int q;cin>>q;
    seg.init(n , n);
    vector<vector<int>>v(n , vector<int>(n));
    for(auto &val:v) {
        for(auto &i:val) {
            char x;cin>>x;
            i = (x == '*');
        }
    }
    seg.build(v);
    while(q--) {
        int type , l1 , r1 , l2 , r2;
        cin>>type>>l1>>r1;
        l1-- , r1--;
        if(type == 1) {
            seg.upd(l1 , r1 , 1 - v[l1][r1]);
            v[l1][r1] = 1 - v[l1][r1];
        }else {
            cin>>l2>>r2; l2-- , r2--;
            cout<<seg.qry(l1 , r1 , l2 , r2)<<line;
        }
    }
}