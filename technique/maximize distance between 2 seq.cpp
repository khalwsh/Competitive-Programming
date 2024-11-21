#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        deque<int>a(n) , b(n);
        for(auto &val:a)cin>>val;
        for(auto &val:b)cin>>val;
        sort(a.begin() , a.end());
        sort(b.begin() , b.end());
        int res = 0;
        while(n--) {
            int temp = 2e9;
            for(int i = 0;i < a.size();++i) {
                temp = min(temp , abs(a[i] - b[i]));
            }
            res = max(res , temp);
            b.push_front(b.back());
            b.pop_back();
        }
        cout<<res<<'\n';
    }
}