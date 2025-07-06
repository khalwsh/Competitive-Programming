// same as normal but we keep track of index of l in query
// and we answer offline sweeping for r
// for (auto [l , idx] : queries[i]) {
//      ans[idx] = bs.max_xor(l);
// }
struct Basis{
    static const int LOG = 61;
    ll basis[LOG]{};
    int lt[LOG];
    Basis(){ memset(lt , -1 , sizeof lt); }
    void insert(ll x , int ind){
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(ind > lt[i]){
                swap(basis[i] , x);
                swap(lt[i] , ind);
            }
            x ^= basis[i];
        }
    }
    ll max_xor(int ind){
        ll x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if((x >> i & 1) || lt[i] < ind) continue;
            x ^= basis[i];
        }
        return x;
    }
};