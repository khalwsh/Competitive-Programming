struct matrix {
    int mat[2][2];
    matrix (int a=1,int b=0,int c=0,int d=1){
        mat[0][0]=a % mod;
        mat[0][1]=b % mod;
        mat[1][0]=c % mod;
        mat[1][1]=d % mod;
    }
    matrix operator*(const matrix &b){
        matrix c;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c.mat[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    c.mat[i][j] +=mat[i][k]*b.mat[k][j];
                }
                c.mat[i][j]%=mod;
            }
        }
        return c;
    }
};
matrix FastPower(matrix a, int power){
      matrix res;
      while(power > 0){
          if(power & 1){
              res = res * a;
          }
          power>>=1ll;
          a = a * a;
      }
      return res;
}
int NthFib(int _n){
    if(!_n){
        return 0;
    }
    matrix a(0,1,1,1);
    return FastPower(a,_n).mat[0][0];
}