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
    bool exist(ll x , int ind) {
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(ind > lt[i]){
                return false;
            }
            x ^= basis[i];
        }
        return true;
    }
};