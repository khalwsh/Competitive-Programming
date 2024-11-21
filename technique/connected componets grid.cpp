#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // problem Given n , m , k generate matrix with size n * m and has k connected coponenets either 0 or 1.
    int n,m,k;cin>>n>>m>>k;
    int a[n][m];
    if(n==1||m==1){
        cout<<"YES"<<'\n';
        int num=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout<<num;
                if(k>1) num=1-num,k--;
            }
            cout<<'\n';
        }
    }else if(k==n*m-1){
        cout<<"NO\n";
    }else{
        cout<<"YES\n";
        int num=0;
        int flag=0;
        if((k+1)%m==0) k--,flag=1;
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                a[i][j]=num;
                num=1-num;
                k--;
                if(k<=0) break;
            }
            if(k<=0) break;
            if(m%2==0) num=1-num;
        }
        if(i==0){
            for(int x=j+1;x<m;x++) a[i][x]=1-num;
        }else if(j+1<m){
            a[i][j+1]=num;
        }
        for(int x=0;x<m;x++){
            int st;
            if(x<=j+1||i==0) st=i;
            else st=i-1;
            for(int y=st+1;y<n;y++) a[y][x]=a[st][x];
        }
        if(flag) a[n-1][m-1]=1-a[n-1][m-2];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout<<a[i][j];
            }
            cout<<"\n";
        }
    }

}
