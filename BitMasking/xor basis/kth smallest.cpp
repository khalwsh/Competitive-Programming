const int BITs = 30;
int basis[BITs + 1];
int comp_sz = 0;
void insert(int msk) {
    for (int i = BITs; i >= 0;i--) {
        if (!(msk >> i & 1))continue;
        if (!basis[i]) {
            comp_sz++;
            basis[i] = msk;
            return;
        }
        msk ^= basis[i];
    }
}
int get(int k){
    // Finding the k-th (one base) smallest xor_sum of all different subsequence xor_sum
    int low = 1 << comp_sz;
    int x = 0;
    for(int i = BITs; i >= 0; --i){
        if(!basis[i]) continue;
        low /= 2;
        if( (!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k) ){
            x ^= basis[i];
        }
        if(low < k) k -= low;
    }
    return x;
}