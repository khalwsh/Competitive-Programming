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
ull get(ull msk) {
    for (int i = BITs;i >= 0;i--) {
        if (msk >> i & 1) continue;
        msk ^= basis[i];
    }
    return msk;
}