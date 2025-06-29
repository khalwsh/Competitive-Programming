template<typename T>
struct SparseTable {
    int n, LG;
    vector<int> LOG;
    vector<vector<pair<T,int>>> sp;
    function<pair<T,int>(const pair<T,int>&, const pair<T,int>&)> comb;

    void init(const vector<T>& arr,function<pair<T,int>(const pair<T,int>&, const pair<T,int>&)> _comb){
        n = arr.size();
        comb = _comb;
        LOG.assign(n+1, 0);
        for(int i = 2; i <= n; ++i)
            LOG[i] = LOG[i/2] + 1;
        LG = LOG[n];
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

    pair<T,int> query(int l, int r) const {
        int len = r - l + 1;
        int k = LOG[len];
        return comb(sp[k][l], sp[k][r - (1<<k) + 1]);
    }

    pair<T,int> query_log(int l, int r) const {
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