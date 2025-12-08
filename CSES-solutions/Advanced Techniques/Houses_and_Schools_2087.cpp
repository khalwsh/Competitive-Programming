/* problem statement text */
/*
CSES - Houses and Schools

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn houses on a street, numbered 1,2,…,n1,2,\dots,n1,2,…,n. The distance of houses aaa and bbb is ∣a−b∣|a-b|∣a−b∣. You know the number of children in each house.
Your task is to establish kkk schools in such a way that each school is in some house. Then, each child goes to the nearest school. What is the minimum total walking distance of the children if you act optimally?
Input
The first input line has two integers nnn and kkk: the number of houses and the number of schools. The houses are numbered 1,2…,n1,2\dots,n1,2…,n.
After this, there are nnn integers c1,c2,…,cnc_1,c_2,\dots,c_nc1​,c2​,…,cn​: the number of children in each house.
Output
Print the minimum total distance.
Constraints

1≤k≤n≤30001 \le k \le n \le 30001≤k≤n≤3000
1≤ci≤1091 \le c_i \le 10^91≤ci​≤109

Example
Input:
6 2
2 7 1 4 6 4

Output:
11

Explanation: Houses 2 and 5 will have schools.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
#define chmin(x,y) x=min(x,y)
/*
 * Description: Container where you can add lines of the form kx+m, and query minimum values at points x.
 * Can be applied on:
    - monotonic slopes, monotonic queries
    - monotonic slopes, random queries
 
   Here's monotonic can be (ASCE , DESC)
 */
struct mnCHT {  // Convex Hull Trick for Minimum
    deque<long long> A; // Slopes
    deque<long long> B; // Intercepts
 
 
    bool bad(int l1, int l2, int l3) {
        return (B[l3] - B[l1]) * (long double) (A[l1] - A[l2])
                <= (B[l2] - B[l1]) * (long double) (A[l1] - A[l3]);
    }
 
    // Adds a line with slope `a` and intercept `b` when slopes are in ascending order
    void addASC(long long a, long long b) {
        A.push_back(a);
        B.push_back(b);
        // Remove the second last line if it's unnecessary
        while (A.size() >= 3 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
            A.erase(A.end() - 2);
            B.erase(B.end() - 2);
        }
    }
 
    // Adds a line with slope `a` and intercept `b` when slopes are in descending order
    void addDESC(long long a, long long b) {
        A.push_front(a);
        B.push_front(b);
        // Remove the second line if it's unnecessary
        while (A.size() >= 3 && bad(0, 1, 2)) {
            A.erase(A.begin() + 1);
            B.erase(B.begin() + 1);
        }
    }
 
    // Evaluates the line at index `l` for a given `x`
    long long f(int l, long long x) {
        return A[l] * x + B[l];
    }
 
    // Queries the convex hull for minimum value at `x` when x-values are increasing
    long long queryASC(long long x) {
        while (A.size() >= 2 && f(0, x) > f(1, x)) {
            // Remove the front line if it's not optimal
            A.pop_front();
            B.pop_front();
        }
        if (A.empty())
            return LLONG_MAX;  // Return maximum value if no lines are left
        return f(0, x);
    }
    // Queries the convex hull for minimum value at `x` when x-values are decreasing
    long long queryDESC(long long x) {
        while (A.size() >= 2 && f(A.size() - 1, x) > f(A.size() - 2, x)) {
            // Remove the back line if it's not optimal
            A.pop_back();
            B.pop_back();
        }
        if (A.empty())
            return LLONG_MAX;  // Return maximum value if no lines are left
        return f(A.size() - 1, x);
    }
 
    // Optional: Query for random x-values using binary search
    long long query(long long x) {
        int lo = 0, hi = A.size() - 1;
        long long res = LLONG_MAX;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            long long val = f(mid, x);
            res = min(res, val);
            if (mid + 1 < A.size() && f(mid + 1, x) <= val) {
                lo = mid + 1;
            } else if (mid - 1 >= 0 && f(mid - 1, x) <= val) {
                hi = mid - 1;
            } else {
                break;
            }
        }
        return res;
    }
};
const ll inf = 1e18;
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n , K; cin >> n >> K;
    int c[n+1];
    for(int i = 1; i <= n; ++i) cin >> c[i];
 
    ll p[n+1]{} , pp[n+1]{};
    for(int i = 1; i <= n; ++i){
        p[i] = p[i-1] + c[i];
        pp[i] = pp[i-1] + 1LL*i*c[i];
    }
 
    ll dp1[K+1][n+1]{} , dp2[K+1][n+1]{};
    for(int i = 0; i <= K; ++i) for(int j = 0; j <= n; ++j) dp1[i][j] = dp2[i][j] = inf;
    dp1[0][0] = dp2[0][0] = 0;
 
    // LineContainerMin G[k+1];
    mnCHT L1[K+1] , L2[K+1];
 
    for(int k = 1; k <= K; ++k){
        L1[k-1].addASC(0,0);
        for(int i = 1; i <= n; ++i){
            /*compute dp1[i]*/
 
            // compute answer
            ll c = 1LL*i*p[i] - pp[i];
            ll x = i;
            dp1[k][i] = L1[k-1].queryASC(x) + c;
            // insert Line
            ll slope = -p[i] , m = pp[i] + dp2[k-1][i];
            L1[k-1].addASC(slope,m);
 
            /*compute dp2[i]*/
 
            // compute dp2[i]
            slope = -i , m = -pp[i]+dp1[k][i]+1LL*i*p[i];
            // insert Line
            L2[k].addASC(slope,m);
            // Compute answer
            c = pp[i];
            x = p[i];
            dp2[k][i] = L2[k].queryASC(x) + c;
 
        }
    }
    cout << dp2[K][n];
}