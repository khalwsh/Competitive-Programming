struct Query {
    int l, r, idx;
    int ord;
    static int rotateDelta[4];
    Query(int L,int R,int Idx){
        idx = Idx;
        l = L;
        r = R;
        ord = gilbertOrder(l,r,21,0);
    }
    bool operator<( const Query &b)const {
        return ord < b.ord;
    }
    int gilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) {
            return 0;
        }
        int hpow = 1 << (pow-1);
        int seg = (x < hpow) ? (
                (y < hpow) ? 0 : 3
        ) : (
                          (y < hpow) ? 1 : 2
                  );
        seg = (seg + rotate) & 3;
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int Nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2*pow - 2);
        int64_t ans = seg * subSquareSize;
        int64_t add = gilbertOrder(nx, ny, pow-1, Nrot);
        ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ans;
    }
};
int Query::rotateDelta[4] = {3, 0, 0, 1};
void add(int MoIdx){

}
void remove(int MoIdx){

}
void Mo(vector<Query> &queries){
    int MoLeft = 0,MoRight = -1;
    for(auto &q: queries){
        while(MoRight < q.r) add(++MoRight);
        while(MoLeft > q.l) add(--MoLeft);
        while(MoRight > q.r) remove(MoRight--);
        while(MoLeft < q.l) remove(MoLeft++);
        //res[q.id] = cnt;
    }
}