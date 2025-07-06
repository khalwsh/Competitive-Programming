int extended_euclidean(int a,int b,int &x,int &y)
{
    if(a<0)
    {
        int r= extended_euclidean(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        int r= extended_euclidean(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int sol= extended_euclidean(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}