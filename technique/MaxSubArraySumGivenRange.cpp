int n;
int v[N],pre[N];
int query(int l,int r){
    return pre[r]-(l==0?0:pre[l-1]);
}
const int k=24;
int sp[k][N];
int dp[N][2];
void build(){
    for(int i=0;i<n;i++)sp[0][i]=pre[i];
    for(int i=1;i<k;i++){
        for(int j=0;j+(1<<i)<=n;j++){
            sp[i][j]=max(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);
        }
    }
}
int Mx(int l,int r){
    if(r-l+1<=0)return 0;
    int lg= log2_floor(r-l+1);
    return max(sp[lg][l],sp[lg][r-(1<<lg)+1]);
}
int solve(int index,int state,int a,int b){
    if(index>n)return -inf;
    if(index==n)return (state==1?0:-inf);
    int &ret=dp[index][state];
    if(~ret)return ret;
    if(state==0){
        int leave=solve(index+1,state,a,b);
        if(index+a>n)return leave;
        int take=solve(index+a,1,a,b)+ query(index,index+a-1);
        return ret=max(leave,take);
    }else{
        if(a==b)return 0;
        int res=Mx(index,min(n-1,index+b-a-1))-(index==0?0:pre[index-1]);
        return ret=max(0ll,res);
    }
}
int MaxSubArraySum(int a,int b,bool ConsiderEmptySubArray = false){
    if(a>n){
        return 0;
    }
    for(int i=0;i<n;i++)memset(dp[i],-1,sizeof dp[i]);
    for(int i=0;i<n;i++)pre[i]=v[i],pre[i]+=(i==0?0:pre[i-1]);
    build();
    if(ConsiderEmptySubArray)return max(0ll,solve(0,0,a,b));
    return solve(0,0,a,b);
}