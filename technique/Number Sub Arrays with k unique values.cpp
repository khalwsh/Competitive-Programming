int SubArraysWithAtMostKUnique(vector<int>&v,int k){
    int n = (int)v.size();
    multiset<int>ms;set<int>s;
    int left=0,right=0;
    int res=0;
    while(right!=n){
        ms.insert(v[right]);
        s.insert(v[right]);
        if(s.size()>k){
            while(s.size()>k){
                ms.erase(ms.find(v[left]));
                if(ms.find(v[left])==ms.end())s.erase(v[left]);
                left++;
            }
        }
        res+=right-left+1;
        right++;
    }
    return res;

}
int SubArraysWithKUnique(vector<int>& v, int k) {
    return SubArraysWithAtMostKUnique(v,k) - SubArraysWithAtMostKUnique(v,k-1);
}