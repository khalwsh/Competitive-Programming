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
int ModInverse(int a,int m){
    int x,y;
    int g = gcd_euldien_algo(a,m,x,y);
    return (g==1?(x%m+m)%m:-inf);
//return -inf if there is no mod inverse
}