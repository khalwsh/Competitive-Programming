int n,m;
int k;
int v[21][21];
map<int,int>values[21][21];
void gen(int i,int j,int steps,int xoring){
    if(!valid(i,j,n,m))return;
    if(steps==0){
        values[i][j][xoring ^ v[i][j]]++;
        return;
    }
    gen(i+1,j,steps-1,xoring^v[i][j]);
    gen(i,j+1,steps-1,xoring^v[i][j]);
}
int res = 0;
void ans(int i,int j,int steps,int xoring){
    if(!valid(i,j,n,m))return;
    if(steps==0){
        //cout<<i<<" "<<j<<line;
        if(values[i][j].count(xoring ^ k))res +=values[i][j][xoring ^ k];
        return;
    }
    ans(i-1,j,steps-1,xoring ^ v[i][j]);
    ans(i,j-1,steps-1,xoring ^ v[i][j]);
}
signed main() {
    khaled
    cin>>n>>m>>k;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>v[i][j];
    int total_steps = n + m - 2;
    gen(0,0,total_steps/2,0);
    total_steps -= total_steps/2;
    ans(n-1,m-1,total_steps,0);
    cout<<res<<line;
}