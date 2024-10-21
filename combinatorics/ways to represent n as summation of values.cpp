#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--) {
        int a , b;cin>>a>>b;
        int x = a & b;
        cout<<((a ^ x) + (b ^ x))<<'\n';
    }
}
int sum(int n , int m = 0){
    if(!m)return (1LL << (n - 1));
    return fast_power(2ll , n - 1 , m);
}