int n;
array<int,3>segments[N]; // L , R , Idx
vector<int>contain(){
    ordered_multiset<int>os;
    for(int i = 0;i<n;i++)os.insert(segments[i][1]);
    sort(segments , segments + n , [](array<int , 3>&a , array<int , 3>&b)->bool {
        if(a[0] != b[0])return a[0] < b[0];
        return a[1] > b[1];
    });
    vector<int>res(n);
    for(int i = 0;i<n;++i) {
        os.erase(os.find_by_order(os.order_of_key(segments[i][1])));
        res[segments[i][2]] = (int)os.order_of_key(segments[i][1] + 1);
    }
    return res;
}
vector<int>contained(){
    ordered_multiset<int>x;
    for(int i = 0;i<n;i++)x.insert(segments[i][1]);
    sort(segments , segments + n, [](auto a, auto b) {
            auto [a1, a2, a3] = a;
            auto [b1, b2, b3] = b;
            if (a1 != b1) return a1 > b1;
            return a2 < b2;
    });

    vector<int> ans2(n);
    for (int j = 0 ;j < n;j ++) {
        int b = segments[j][1];
        int i = segments[j][2];
        x.erase(x.find_by_order(x.order_of_key(b)));
        ans2[i] = (int)x.size() - x.order_of_key(b);
    }
    return ans2;
}