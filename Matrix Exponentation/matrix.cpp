template<class T>
struct Matrix {
    vector<vector<T>>v;
    int n , m;
    Matrix(int n , int m): n(n) , m(m) , v(vector<vector<T>>(n , vector<T>(m , 0))){}
    Matrix<T> operator*(const Matrix<T>&other) {
        assert(m == other.n);
        Matrix<T>res(n , other.m);
        for(int i = 0;i < n;i++) {
            for(int k = 0;k < m;k++) {
                if(v[i][k] == 0)continue;
                for(int j = 0;j < other.m;j++) {
                    res.v[i][j] += v[i][k] * other.v[k][j];
                }
            }
        }
        return res;
    }
    Matrix<T> power(ll k) {
        assert(n == m);
        Matrix<T>res(n , m);
        Matrix a = *this;
        for(int i = 0;i < n;i++)res.v[i][i] = 1;
        while(k > 0) {
            if(k & 1) {
                res = res * a;
            }
            a = a * a;
            k >>=1;
        }
        return res;
    }

    Matrix<T> operator+(const Matrix<T> &b){
        assert(n == b.n && m == b.m);
        Matrix<T> res(b.n , b.m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                res.v[i][j] = v[i][j] + b.v[i][j];
            }
        }
        return res;
    }

    Matrix<T> Identity(int n , int m) {
        assert(n == m);
        Matrix<T> res(n ,m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.v[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            res.v[i][i] = 1;
        }
        return res;
    }

    Matrix<T> Spower(ll k) {
        if(k == 0)return Matrix(n , m);
        if (k & 1) {
            return *this * (Identity(n , m) + Spower(k - 1));
        }
        return Spower(k / 2) * (Identity(n , m) + power(k / 2));
    }
};