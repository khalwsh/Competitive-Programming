int stirling_number(int n,int k){
    if(k==0)return n==0;
    if(n==0)return 0;
    return stirling_number(n-1,k-1)+(n-1)* stirling_number(n-1,k);
    //S[i][j]=S[i-1][j-1]+s[i-1][j]*(i-1)
    //S(n,k) as the different ways to cut n different elements into k undifferentiated non-empty subsets. For example, S(5,3) denotes to:25
}