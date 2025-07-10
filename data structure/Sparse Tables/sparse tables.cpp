template<typename T>
struct SparseTable {
    const int LG = 20;
    int n;
    vector<vector<pair<T,int>>> sp;
    function<pair<T,int>(const pair<T,int>&, const pair<T,int>&)> comb;


    int log2_floor(int i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
    void init(const vector<T>& arr,function<pair<T,int>(const pair<T,int>&, const pair<T,int>&)> _comb){
        n = arr.size();
        comb = _comb;
        sp.assign(LG+1, vector<pair<T,int>>(n));
        for(int i = 0; i < n; ++i)
            sp[0][i] = { arr[i], i };

        build();
    }

    void build() {
        for(int k = 1; k <= LG; ++k) {
            int len = 1 << (k-1);
            for(int i = 0; i + (1<<k) <= n; ++i) {
                sp[k][i] = comb(sp[k-1][i], sp[k-1][i + len]);
            }
        }
    }

    pair<T,int> query(int l, int r) {
        int k = log2_floor(r - l + 1);
        return comb(sp[k][l], sp[k][r - (1<<k) + 1]);
    }

    pair<T,int> query_log(int l, int r) {
        int remaining = r - l + 1;
        pair<T,int> res = {T(), -1};
        for(int k = LG; k >= 0; --k) {
            if ((1<<k) <= remaining) {
                if (res.second == -1)
                    res = sp[k][l];
                else
                    res = comb(res, sp[k][l]);
                l += 1<<k;
                remaining -= 1<<k;
            }
        }
        return res;
    }
};