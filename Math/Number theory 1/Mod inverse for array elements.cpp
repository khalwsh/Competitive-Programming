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
vector<int> invs(const std::vector<int> &a, int m) {
    int n = (int)a.size();
    if (n == 0) return {};
    std::vector<int> b(n);
    int v = 1;
    for (int i = 0; i != n; ++i) {
        b[i] = v;
        v = static_cast<long long>(v) * a[i] % m;
    }
    int x, y;
    extended_euclidean(v, m, x, y);
    x = (x % m + m) % m;
    for (int i = n - 1; i >= 0; --i) {
        b[i] = static_cast<long long>(x) * b[i] % m;
        x = static_cast<long long>(x) * a[i] % m;
    }
    return b;
}