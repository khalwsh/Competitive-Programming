// send permutation in zero base , kth start from 0
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