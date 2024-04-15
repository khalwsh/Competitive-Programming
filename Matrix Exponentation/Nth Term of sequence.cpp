struct matrix {
    int siz;
    vector<vector<int>>mat;
    matrix(int _siz) {
        mat.resize(_siz,vector<int>(_siz));
        siz = _siz;
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                mat[i][j] = 0;
            }
        }
    }

    matrix operator*(const matrix &b) {
        matrix c(siz);
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                c.mat[i][j] = 0;
                for (int k = 0; k < siz; k++) {
                    c.mat[i][j] += mul(mat[i][k] , b.mat[k][j],mod);
                }
                c.mat[i][j] %= mod;
            }
        }
        return c;
    }

    matrix operator+(const matrix &b){
        matrix res(siz);
        for(int i = 0; i < siz; i++){
            for(int j = 0; j < siz; j++){
                res.mat[i][j] = mat[i][j] + b.mat[i][j];
                res.mat[i][j] %= mod;
            }
        }
        return res;
    }

    int Trace() {
        int sum = 0;
        for (int i = 0; i < siz; i++)sum += mat[i][i] % mod;
        return sum % mod;
    }
};
matrix Identity(int siz) {
    matrix res(siz);
    for (int i = 0; i < siz; i++) {
        for (int j = 0; j < siz; j++) {
            res.mat[i][j] = 0;
        }
    }
    for (int i = 0; i < siz; i++) {
        res.mat[i][i] = 1;
    }
    return res;
}
matrix ZeroMatrix(int siz) {
    matrix res(siz);
    return res;
}
matrix FastPower(matrix a, int power) {
    matrix res = Identity(a.siz);
    while (power > 0) {
        if (power & 1) {
            res = res * a;
        }
        power >>= 1ll;
        a = a * a;
    }
    return res;
}
matrix Rotation(const matrix &a){
    matrix res(a.siz);
    int siz = a.siz;
    for(int i = 0; i < siz; i++){
        for(int j = 0; j < siz; j++){
            res.mat[j][siz - 1 - i] = a.mat[i][j];
        }
    }
    return res;
}
matrix Reflection(const matrix &a){
    matrix res(a.siz);
    int siz = a.siz;
    for(int i = 0; i < siz; i++){
        for(int j = 0; j < siz; j++){
            res.mat[i][siz - 1 - j] = a.mat[i][j];
        }
    }
    return res;
}
matrix SumPowers(matrix &a , int _n) {
    if (_n == 0) return ZeroMatrix(a.siz);
    if (_n & 1) {
        return a * (Identity(a.siz) + SumPowers(a, _n - 1));
    } else {
        return SumPowers(a, _n / 2) * (Identity(a.siz) + FastPower(a, _n / 2));
    }
}
int NthTerm(vector<int>&FirstKthTerms,vector<int>&Cof,int n) {
    int k = (int) FirstKthTerms.size();
    matrix base(k);
    for (int i = 0; i < k; ++i) {
        base.mat[i][0] = FirstKthTerms[i];
    }
    matrix trans(k);
    reverse(Cof.begin(), Cof.end());
    for (int i = 1; i < k; i++) {
        trans.mat[i - 1][i] = 1;
    }
    for (int i = 0; i < k; i++) {
        trans.mat[k - 1][i] = Cof[i];
    }
    matrix res = FastPower(trans, n - 1) * base;
    return res.mat[0][0];
}