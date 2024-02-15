int gcd_euldien_algo(int a,int b,int &x,int &y)
{
    if(a<0)
    {
        int r= gcd_euldien_algo(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        int r= gcd_euldien_algo(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int sol= gcd_euldien_algo(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd_euldien_algo(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    g = abs(g);
    return true;                             // a*x + b*y = c     //__gcd(a,b)|c
}
// x0 contain the x cofficent
// y0 contain the y cofficent
// g  contain the gcd


// to get more solutions we can x0 = x0 +k*b/g
//                              y0 = y0 -k*a/g
int LinearCongruenceEquation(int a,int b,int m){
    int x,y,g;
    if(find_any_solution(a,m,b,x,y,g)){
        return (x%m+m)%m;
    }
    return -inf;
}
// solve a * x [=] b % n
// [=]-----> congruence
// to find the value of x if exist you solve     a * x + n * k = b by linear Diophantian equation