int BLOCK_SIZE = 317;
struct Query{
    int l , r,id;
    bool operator < (const Query &other) const{
        int n1 = l / BLOCK_SIZE, n2 = other.l / BLOCK_SIZE;
        if(n1 != n2) return n1 < n2;
        return (n1 % 2) ? r > other.r : r < other.r;
    }
};
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