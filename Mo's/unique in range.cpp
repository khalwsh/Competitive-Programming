//ex:how many unique element in given range

int freq[1000001];
struct query{
    //Mo's algorithm
    //o(Q*sqrt(n)+2*n*sqrt(n)+n)
    int l,r,BlockId,idx;
    void fill(int ll,int rr,int B,int i){
        l=ll,r=rr,BlockId=B,idx=i;
    }
    query()=default;
    query(int a,int b,int c,int i){
        fill(a,b,c,i);
    }
    bool operator<(const query& second){
        if(BlockId!=second.BlockId)return BlockId<second.BlockId;
        return r<second.r;
    }
};
void DQuery(){
    int n;
    cin>>n;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    int q;
    cin>>q;
    int SQ=ceil(sqrt(n)+.01);
    vector<query>queries;
    int cnt=0;
    int t=q;
    while(t--){
        int l,r;
        cin>>l>>r;
        l--,r--;
        if(l>r)swap(l,r);
        queries.emplace_back(l,r,l/SQ,cnt++);
    }
    sort(queries.begin(),queries.end());
    vector<int>ans(q);
    int l=0,r=-1;
    int res=0;
    for(auto &val:queries){
        int start=val.l,ending=val.r;
        int idx=val.idx;
        while(l<start){
            freq[v[l]]--;
            if(freq[v[l]]==0)res--;
            l++;
        }
        while(l>start){
            l--;
            if(freq[v[l]]==0)res++;
            freq[v[l]]++;
        }
        while(r<ending){
            r++;
            if(freq[v[r]]==0)res++;
            freq[v[r]]++;
        }
        while(r>ending){
            freq[v[r]]--;
            if(freq[v[r]]==0)res--;
            r--;
        }
        ans[idx]=(int)res;
    }
    for(auto &val:ans)cout<<val<<line;
}