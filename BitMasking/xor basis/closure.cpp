const int BITs = 63;
ull basis[BITs + 1];
int comp_sz = 0;
void insert(ull msk) {
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
// min # elements needed to be inserted to make each subset xor exist within the array
ll xor_closure(int unique_elements) {
    int res = 0;
    for (int i = BITs;i >= 0;i--) {
        if (!basis[i]) continue;
        res++;
    }
    return (1LL << res) - unique_elements;
}