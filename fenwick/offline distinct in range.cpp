/* the idea is to sort the queries from large l to smallest and maintain map
   of left most index a value appear in and whenever you find query has l == i where i iterating from n - 1
   you handle those queries and when you see a value exist in the map you Update it's postion with -1 and update
   the map_postion with i then update this postion in fenwick with 1
*/
int n,q;
int v[N];
vector<pair<int,int>>queries[N];
int ans[N];
struct Fenwick{
    int n;
    vector<int>tree;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
    }
    void add(int pos,int value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    int get(int pos) {
        int sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    int query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};

signed main() {
    khaled
    cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    Fenwick fen;
    fen.init(n);
    map<int,int>last_index;
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        queries[l].emplace_back(r,i);
    }
    for(int i=n-1;i>=0;i--){
        int val = v[i];
        if(last_index.count(val)){
            fen.add(last_index[val],-1);
        }
        last_index[val] = i;
        fen.add(i,1);
        for(auto &j:queries[i]){
            ans[j.second] = fen.get(j.first);
        }
    }
    for(int i=0;i<q;i++){
        cout<<ans[i]<<line;
    }
}