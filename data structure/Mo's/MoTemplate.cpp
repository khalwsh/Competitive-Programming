int BLOCK_SIZE = 317;
struct Query{
    int l , r,id;
    bool operator < (const Query &other) const{
        int n1 = l / BLOCK_SIZE, n2 = other.l / BLOCK_SIZE;
        if(n1 != n2) return n1 < n2;
        return (n1 % 2) ? r > other.r : r < other.r;
    }
};
void add(int MoIdx , bool dir){
    // dir 0 left add , dir 1 right add
}
void remove(int MoIdx , bool dir){
    // dir 0 left-remove , dir 1 right remove
}
void Mo(vector<Query> &queries){
    int MoLeft = 0,MoRight = -1;
    for(auto &q: queries){
        while(MoRight < q.r) add(++MoRight , 1);
        while(MoLeft > q.l) add(--MoLeft , 0);
        while(MoRight > q.r) remove(MoRight-- , 1);
        while(MoLeft < q.l) remove(MoLeft++ , 0);
//        res[q.id] = cnt;
    }
}