template<typename T>
struct segTree_2d{
    vector<vector<T>> t;
    int n , m;
    template<typename ContainerType>
    void init(int n, int m , vector<vector<ContainerType>> &g){
        this->n = n;
        this->m = m;
        int r = 1 , c = 1;
        while(r < n) r *= 2;
        while(c < m) c *= 2;
        t = vector<vector<T>>(2 * r , vector<T>(2 * c));    
        build(g);
        
    }
    template<typename ContainerType>
    void build_y(int vx, int lx, vector<vector<ContainerType>> &g ,int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx){
                t[vx][vy] = g[lx][ly];
            }
            else{
                t[vx][vy] = merge(t[vx*2][vy] , t[vx*2+1][vy]);
            }
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, g, rx, vy*2, ly, my);
            build_y(vx, lx, g, rx, vy*2+1, my+1, ry);
            t[vx][vy] = merge(t[vx][vy*2] , t[vx][vy*2+1]);
        }
    }
    template<class ContainerType>
    void build_x(vector<vector<ContainerType>> &g , int vx, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(g , vx*2, lx, mx);
            build_x(g , vx*2+1, mx+1, rx);
        }
        build_y(vx, lx, g, rx, 1, 0, m-1);
    }
    T qry_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry) 
            return 0;
        if (ly == tly && try_ == ry)
            return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return merge(qry_y(vx, vy*2, tly, tmy, ly, min(ry, tmy))
             , qry_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry));
    }
 
    T qry_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return 0;
        if (lx == tlx && trx == rx)
            return qry_y(vx, 1, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return merge(qry_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry)
             , qry_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry));
    }
    T merge(T a , T b){ return __gcd(a , b);}
    template<typename ContainerType>
    void build(vector<vector<ContainerType>> &g){ build_x(g , 1 , 0 , n - 1); }
    int qry(int x , int y , int xx , int yy){ return qry_x(1 , 0 , n - 1 , x , xx , y , yy); }
};