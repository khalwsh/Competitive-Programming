int res[N] , ans = 0;
//struct
const int SQ = 400;
struct Query{
    int l,r,idx;
    Query(int a = 0,int b = 0,int c = 0){
        l = a;
        r = b;
        idx = c;
    }
    bool operator<(const Query & a){
        return make_pair(l/SQ,r) < make_pair(a.l/SQ,a.r);
    }
};
// main part
for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;l--,r--;
        queries.emplace_back(Query{l,r,i});
    }
    sort(queries.begin(),queries.end());
    int MoLeft = 0,MoRight = -1;
    // O( q * BlockSize + n + 2 * n * n/BlockSize) ---- make differentiation for BlockSize and get LocalMin
    for(auto &val:queries){
        int idx = val.idx;
        int l = val.l;
        int r = val.r;
        while(MoRight<r){
            MoRight++;
            //code insert
        }
        while(MoLeft>l){
            MoLeft--;
            //code insert
        }
        while(MoRight>r){
            //code delete
            MoRight--;
        }
        while(MoLeft<l){
            //code delete
            MoLeft++;
        }
        res[idx] = ans;
    }