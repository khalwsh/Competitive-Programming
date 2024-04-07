struct matrix {
    static const int siz = 2;
    int mat[siz][siz];

    matrix() {
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                mat[i][j] = 0;
            }
        }
    }

    matrix operator*(const matrix &b) {
        matrix c;
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                c.mat[i][j] = 0;
                for (int k = 0; k < siz; k++) {
                    c.mat[i][j] += mat[i][k] * b.mat[k][j];
                }
                c.mat[i][j] %= mod;
            }
        }
        return c;
    }

    matrix operator+(const matrix &b){
        matrix res = ZeroMatrix();
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

    static matrix Identity() {
        matrix res;
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

    static matrix ZeroMatrix() {
        matrix res;
        return res;
    }

    static matrix FastPower(matrix a, int power) {
        matrix res = matrix::Identity();
        while (power > 0) {
            if (power & 1) {
                res = res * a;
            }
            power >>= 1ll;
            a = a * a;
        }
        return res;
    }

    static matrix Rotation(const matrix &a){
        matrix res = ZeroMatrix();
        for(int i = 0; i < siz; i++){
            for(int j = 0; j < siz; j++){
                res.mat[j][siz - 1 - i] = a.mat[i][j];
            }
        }
        return res;
    }

    static matrix Reflection(const matrix &a){
        matrix res = ZeroMatrix();
        for(int i = 0; i < siz; i++){
            for(int j = 0; j < siz; j++){
                res.mat[i][siz - 1 - j] = a.mat[i][j];
            }
        }
        return res;
    }

    static matrix SumPowers(matrix &a , int _n) {
        if (_n == 0) return ZeroMatrix();
        if (_n & 1) {
            return a * (Identity() + SumPowers(a, _n - 1));
        } else {
            return SumPowers(a, _n / 2) * (Identity() + FastPower(a, _n / 2));
        }
    }
};
