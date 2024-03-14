struct fenwick_2D{
    int n;
    vector<vector<int>>tree;
    void init(int _n){
        this->n=_n;
        tree.resize(n,vector<int>(n));
    }
    fenwick_2D(int _n=0){
        this->n=_n;
        tree.resize(n,vector<int>(n));
    }
    void update(int x,int y,int delta){
        for(++x;x<=n;x+=x&-x){
            for(int j=y+1;j<=n;j+=j&-j){
                tree[x-1][j-1]+=delta;
            }
        }
    }
    int get(int x,int y){
        int sum=0;
        for(++x;x;x-=x&-x){
            for(int j=y+1;j;j-=j&-j){

                sum+=tree[x-1][j-1];
            }
        }
        return sum;
    }
    int get(int x1,int y1,int x2,int y2){
        return get(x2,y2)-get(x2,y1-1)-get(x1-1,y2)+get(x1-1,y1-1);
    }
};

