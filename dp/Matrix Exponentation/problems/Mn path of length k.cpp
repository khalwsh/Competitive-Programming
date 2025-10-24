struct matrix {
    int siz;
    vector<vector<int>>mat;
    matrix(int _siz) {
        mat.resize(_siz,vector<int>(_siz,inf));
        siz = _siz;
    }

    matrix operator*(const matrix &b) {
        matrix c(siz);
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                for (int k = 0; k < siz; k++) {
                    c.mat[i][k] =min(c.mat[i][k],mat[i][j] + b.mat[j][k]);
                }
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
    matrix res(a.siz);
    for(int i=0;i<res.siz;i++)res.mat[i][i] = 0;
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
matrix FastSumPowers(matrix &a,int k){
    int _n = a.siz;
    matrix res(2 * _n);
    for(int i=0;i<_n;i++){
        for(int j=0;j<_n;j++){
            res.mat[i][j] = a.mat[i][j];
        }
    }
    for(int i=_n;i<2*_n;i++){
        for(int j = 0;j<_n;j++){
            res.mat[i][j] = a.mat[i-_n][j];
        }
    }
    for(int i=_n;i<2*_n;i++){
        for(int j=0;j<_n;j++){
            res.mat[i][j] = 0;
        }
    }
    for(int i=_n;i<2*_n;i++){
        for(int j=_n;j<2*_n;j++){
            res.mat[i][j] = 0;
            if(i==j)res.mat[i][j] = 1;
        }
    }
    res = FastPower(res,k);
    for(int i=_n;i<2 * _n;i++){
        for(int j=0;j<_n;j++){
            a.mat[i - _n][j] = res.mat[i][j];
        }
    }
    return a;
}
int MnPath(){
    int n,m,k;
    cin>>n>>m>>k;
    matrix M(n);
    for(int i=0;i<m;i++){
        int a,b,c;cin>>a>>b>>c;
        a--,b--;
        M.mat[a][b] = c;
    }
    M = FastPower(M , k);
    int mn = inf;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mn = min(M.mat[i][j],mn);
        }
    }
    return (mn >= inf / 2 ? inf : mn);
}