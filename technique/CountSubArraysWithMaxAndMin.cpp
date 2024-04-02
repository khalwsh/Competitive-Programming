int CountSubArraysWithKnownMxAndMn(vector<int>&v , int mn,int mx){
    int ans=0;
    int maxi=-1, mini=-1;
    int s=(int)v.size();
    for(int r=0, l=0; r<s; r++){
        int x=v[r];
        if (x<mn ||x>mx){
            l=r+1;
            continue;
        }
        if (x==mx) maxi=r;
        if (x==mn) mini=r;
        ans+=max((min(maxi, mini)-l+1),0ll);
    }
    return ans;
}