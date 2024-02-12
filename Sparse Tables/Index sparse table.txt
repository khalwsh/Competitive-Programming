const int k = 20;
int sp1[k][N];//max
int sp2[k][N];//min
void build(int n,vector<int>&v){
    for(int i = 1;i<k;i++){
        for(int j = 0;j+(1<<i)<=n;j++){
            if(v[sp1[i-1][j]]>v[sp1[i-1][j+(1<<(i-1))]]){
                sp1[i][j]=sp1[i-1][j];
            }else{
                sp1[i][j]=sp1[i-1][j+(1<<(i-1))];
            }
            if(v[sp2[i-1][j]]>v[sp2[i-1][j+(1<<(i-1))]]){
                sp2[i][j]=sp2[i-1][j+(1<<(i-1))];
            }else{
                sp2[i][j]=sp2[i-1][j];
            }
        }
    }
}
int query1(int l,int r,vector<int>&v){
    int lg = log2_floor(r-l+1);
    if(v[sp1[lg][l]]>v[sp1[lg][r-(1<<lg)+1]])return sp1[lg][l];
    return sp1[lg][r-(1<<lg)+1];
}
int query2(int l,int r,vector<int>&v){
    int lg = log2_floor(r-l+1);
    if(v[sp2[lg][l]]>v[sp2[lg][r-(1<<lg)+1]])return sp2[lg][r-(1<<lg)+1];
    return sp2[lg][l];
}