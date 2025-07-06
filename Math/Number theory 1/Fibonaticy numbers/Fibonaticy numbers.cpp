F[n] = F[n-1] + F[n-2]

F[n-1]*F[n+1]-(F[n]^2) = (-1)^n

F[n+k] = F[k]*F[n+1]+F[k-1]*F[n]

F[2*n] = F[n]*(F[n+1]+F[n-1])

F[n]|F[n*k] 

if(F[m]%F[n]==0) m%n == 0

GCD(F[m],F[n]) = F[GCD(m,n)]

any number n can be represented uniquely as sum of fibonacci numbers and the representation cann't
have 2 consecutive Fibnoacci numbers

F[n] = ( ((1+sqrt(5))/2)^n - ((1-sqrt(5))/2)^n ) / sqrt(5);

could be simplified to this

F[n] = round(( ((1+sqrt(5))/2)^n ) / sqrt(5));

Fast Fib calculations:

[ 1 1 ]        [ F[n+1] F[n]   ]
        ^ n  =   
[ 1 0 ]        [ F[n]   F[n-1] ]

//implementation

struct Matrix{
    int arr[2][2];
    Matrix(int a=1,int b=1,int c=1,int d=0){
        arr[0][0]=a;
        arr[0][1]=b;
        arr[1][0]=c;
        arr[1][1]=d;
    }
    Matrix operator*(const Matrix & a){
        Matrix res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                int temp = 0;
                for(int k = 0;k<2;k++){
                    temp = add(temp,mul(arr[i][k],a.arr[k][j],mod),mod);
                }
                res.arr[i][j] = temp;
            }
        }
        return res;
    }
};
Matrix MatPow(Matrix base, long long n) {
    Matrix ans (1,0,0,1);
    while (n) {
        if(n&1)
            ans = ans*base;
        base = base*base;
        n >>= 1;
    }
    return ans;
}
long long fib(int n) {
    Matrix base;
    return MatPow(base, n).arr[0][1];
}