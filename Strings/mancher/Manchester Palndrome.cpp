struct Manacher {
	vector<int>p;
	string T;
	void build(string &s) {
		string t;
		T = s;
		for(auto &val:s)t += '#' , t += val;
		t += '#';
		int n = (int)t.size();
		p.resize(n , 1);
		int l = 1 , r = 1;
		for(int i = 1;i < n;i++) {
			p[i] = max(0 , min(r - i , p[l + r - i]));
			while(i - p[i] >= 0 and i + p[i] < n and t[i + p[i]] == t[i - p[i]])p[i]++;
			if(p[i] + i > r) {
				r = i + p[i];
				l = i - p[i];
			}
		}
	}
	int GetLongest(int center , bool odd = true) {
		int NewCenter = 2 * center + !odd + 1;
		return p[NewCenter] - 1;
	}
	bool IsPalndrome(int l , int r) {
		return (r - l + 1) <= GetLongest((l + r) / 2 , l % 2 == r % 2);
	}
	string LongestPalndromeSubStr() {
		int m = 0 , st = -1;
		for(int i = 0;i < T.size();i++) {
			if(GetLongest(i , false) >= m) {
				m = GetLongest(i , false);
				st = i;
			}
			if(GetLongest(i , true) >= m) {
				m = GetLongest(i , true);
				st = i;
			}
		}
		if(m & 1) {
			return T.substr(st - m / 2 , m);
		}
		return T.substr(st - m / 2 + 1 , m);
	}
};