struct BitRange{
    //expected from user to deal with zero base
    int N;
    vector<int>m,c;
    void init(int x){
        N=x;
        m.resize(N),c.resize(N);
    }
    void add(int pos,int mVal,int cVal){
        for(++pos;pos<=N;pos+=pos&-pos){
            m[pos-1]+=mVal;
            c[pos-1]+=cVal;
        }
    }
    int get(int pos){
        int ret=0;
        int x=pos;
        for(pos++;pos;pos-=pos&-pos){
            ret+=m[pos-1]*x+c[pos-1];
        }
        return ret;
    }
    void addRange(int l,int r,int value){
        add(l,value,-value*(l-1));
        add(r+1,-value,value*r);
    }
};
