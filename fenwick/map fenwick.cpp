const int inf = 1e9 + 9;
map<int,int> tree; // LAZY MODIFICATION
struct BIT {
    void add(int x, int val) {
    	for(++x; x < inf; x += (x & -x))  tree[x-1] += val;
    }
    long long sum(int x){
    	long long res = 0;
    	for(++x;x > 0; x -= (x & -x)) res += tree[x-1];
    	return res;
    }
    long long sum(int l , int r){ return sum(r) - sum(l - 1); }
};