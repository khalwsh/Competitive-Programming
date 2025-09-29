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

constexpr int MAXV = 5100; // string length

pair<vector<int>, vector<int> > manacher(const string &s) {
	int n = (int) s.size();
	vector<int> d1(n);
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
		d1[i] = k--;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	vector<int> d2(n);
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
		d2[i] = k--;
		if (i + k > r) {
			l = i - k - 1;
			r = i + k;
		}
	}
	return {d1, d2};
}

struct WaveletTree {
	int lo, hi;
	WaveletTree *L = nullptr, *R = nullptr;
	vector<int> b;
	vector<ll> c;

	WaveletTree() = default;

	void build(vector<int> &arr, int l, int r, int x, int y) {
		lo = x;
		hi = y;
		if (l > r) return;
		if (lo == hi) {
			b.assign(r - l + 2, 0);
			c.assign(r - l + 2, 0);
			for (int i = l; i <= r; ++i) {
				b[i - l + 1] = b[i - l] + 1;
				c[i - l + 1] = c[i - l] + arr[i];
			}
			return;
		}
		int mid = (lo + hi) >> 1;
		b.resize(r - l + 2);
		c.resize(r - l + 2);
		b[0] = 0;
		c[0] = 0;
		for (int i = l; i <= r; ++i) {
			b[i - l + 1] = b[i - l] + (arr[i] <= mid);
			c[i - l + 1] = c[i - l] + arr[i];
		}
		vector<int> left;
		left.reserve(b.back());
		vector<int> right;
		right.reserve((r - l + 1) - b.back());
		for (int i = l; i <= r; ++i) {
			if (arr[i] <= mid) left.push_back(arr[i]);
			else right.push_back(arr[i]);
		}
		int idx = l;
		for (int v: left) arr[idx++] = v;
		for (int v: right) arr[idx++] = v;

		if (!left.empty()) {
			L = new WaveletTree();
			L->build(arr, l, l + (int) left.size() - 1, lo, mid);
		}
		if (!right.empty()) {
			R = new WaveletTree();
			R->build(arr, l + (int) left.size(), r, mid + 1, hi);
		}
	}

	inline int bval(int i) const { return (i >= 0 && i < (int) b.size()) ? b[i] : 0; }

	int kth(int l, int r, int k) const {
		if (l > r) return 0;
		if (lo == hi) return lo;
		int inLeft = b[r] - b[l - 1];
		int lb = b[l - 1];
		int rb = b[r];
		if (k <= inLeft) return L->kth(lb + 1, rb, k);
		return R->kth(l - lb, r - rb, k - inLeft);
	}

	int LTE(int l, int r, int k) const {
		if (l > r || k < lo) return 0;
		if (hi <= k) return r - l + 1;
		int lb = b[l - 1], rb = b[r];
		int res = 0;
		if (L) res += L->LTE(lb + 1, rb, k);
		if (R) res += R->LTE(l - lb, r - rb, k);
		return res;
	}

	int count(int l, int r, int k) const {
		if (l > r || k < lo || k > hi) return 0;
		if (lo == hi) return r - l + 1;
		int lb = b[l - 1], rb = b[r];
		int mid = (lo + hi) >> 1;
		if (k <= mid) return L ? L->count(lb + 1, rb, k) : 0;
		return R ? R->count(l - lb, r - rb, k) : 0;
	}

	ll sum(int l, int r, int k) const {
		if (l > r || k < lo) return 0;
		if (hi <= k) return c[r] - c[l - 1];
		int lb = b[l - 1], rb = b[r];
		ll res = 0;
		if (L) res += L->sum(lb + 1, rb, k);
		if (R) res += R->sum(l - lb, r - rb, k);
		return res;
	}

	~WaveletTree() {
		delete L;
		delete R;
	}
};

inline ll range_sum(ll l, ll r) {
	if (l > r) return 0;
	return r * (r + 1) / 2 - (l - 1) * l / 2;
}

WaveletTree oddL, oddR, evenL, evenR;

ll odd_contrib(int l, int r) {
	int m = (l + r) / 2;
	int c1 = 1 - l;
	int lessL = oddL.LTE(l, m, c1);
	ll ansL = range_sum(l, m) + oddL.sum(l, m, c1) + (ll) (m - l + 1 - lessL) * c1;
	int c2 = 1 + r;
	int lessR = oddR.LTE(m + 1, r, c2);
	ll ansR = -range_sum(m + 1, r) + oddR.sum(m + 1, r, c2) + (ll) (r - m - lessR) * c2;
	return ansL + ansR;
}

ll even_contrib(int l, int r) {
	int m = (l + r) / 2;
	int c1 = -l;
	int lessL = evenL.LTE(l, m, c1);
	ll ansL = range_sum(l, m) + evenL.sum(l, m, c1) + (ll) (m - l + 1 - lessL) * c1;
	int c2 = 1 + r;
	int lessR = evenR.LTE(m + 1, r, c2);
	ll ansR = -range_sum(m + 1, r) + evenR.sum(m + 1, r, c2) + (ll) (r - m - lessR) * c2;
	return ansL + ansR;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;
	int n = (int) s.size();

	auto [d1, d2] = manacher(s);

	vector<int> A(n + 1), B(n + 1), C(n + 1), D(n + 1);
	for (int i = 1; i <= n; ++i) A[i] = d1[i - 1] - i;
	for (int i = 1; i <= n; ++i) B[i] = d1[i - 1] + i;
	for (int i = 1; i <= n; ++i) C[i] = d2[i - 1] - i;
	for (int i = 1; i <= n; ++i) D[i] = d2[i - 1] + i;

	vector<int> tmpA = A, tmpB = B, tmpC = C, tmpD = D;

	oddL.build(tmpA, 1, n, -MAXV, MAXV);
	oddR.build(tmpB, 1, n, -MAXV, MAXV);
	evenL.build(tmpC, 1, n, -MAXV, MAXV);
	evenR.build(tmpD, 1, n, -MAXV, MAXV);

	int q;
	cin >> q;
	for (int qi = 0; qi < q; ++qi) {
		int l, r;
		cin >> l >> r;
		ll ans = odd_contrib(l, r) + even_contrib(l, r);
		cout << ans << '\n';
	}
}
