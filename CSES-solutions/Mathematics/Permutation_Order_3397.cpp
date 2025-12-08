/* problem statement text */
/*
CSES - Permutation Order

Time limit: 1.00 s
Memory limit: 512 MB

Let p(n,k)p(n,k)p(n,k) denote the kkkth permutation (in lexicographical order) of 1…n1 \dots n1…n. For example, p(4,1)=[1,2,3,4]p(4,1)=[1,2,3,4]p(4,1)=[1,2,3,4] and p(4,2)=[1,2,4,3]p(4,2)=[1,2,4,3]p(4,2)=[1,2,4,3].
Your task is to process two types of tests:

Given nnn and kkk, find p(n,k)p(n,k)p(n,k)
Given nnn and p(n,k)p(n,k)p(n,k), find kkk

Input
The first line has an integer ttt: the number of tests.
Each test is either "1 nnn kkk" or "2 nnn p(n,k)p(n,k)p(n,k)".
Output
For each test, print the answer according to the example.
Constraints

1≤t≤10001 \le t \le 10001≤t≤1000
1≤n≤201 \le n \le 201≤n≤20
1≤k≤n!1 \le k \le n!1≤k≤n!

Example
Input:
6
1 4 1
1 4 2
2 4 1 2 3 4
2 4 1 2 4 3
1 5 42
2 5 2 4 5 3 1

Output:
1 2 3 4
1 2 4 3
1
2
2 4 5 3 1
42
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
// build factorials first
const int N = 21;
ll Fact[N];
vector<ll> nthPerm(ll len, ll nth) {
	vector<ll> identity(len), perm(len);
	for (int i = 0;i < len;i++) identity[i] = i;
 
	for (int i = len - 1; i >= 0; --i) {
		ll p = nth / Fact[i];
		perm[len - 1 - i] = identity[p];
		identity.erase(identity.begin() + p);
		nth %= Fact[i];
	}
	return perm;
}
ll PermToIndex(vector<int> perm) {
	ll idx = 0;
	int n = perm.size();
	for (int i = 0; i < n; ++i) {
		// Remove first, and Renumber the remaining elements to remove gaps
		idx += Fact[n-i-1] * perm[i];
		for(int j = i+1; j < n; j++)
			perm[j] -= perm[j] > perm[i];
	}
	return idx;
}
int main() {
    PRE();
	Fact[0] = 1;
	for (int i = 1;i < N;i++) Fact[i] = 1LL * i * Fact[i - 1];
	int t;cin >> t;
	while (t--) {
		int ty;cin >> ty;
		if (ty == 1) {
			ll n , k; cin >> n >> k;
			for (auto &val : nthPerm(n , k - 1)) cout << val + 1 << " ";
			cout << '\n';
		}else {
			int n;cin >> n;
			vector<int>perm(n);
			for (int i = 0;i < n;i++) cin >> perm[i] , perm[i]--;
			cout << PermToIndex(perm) + 1 << '\n';
		}
	}
}