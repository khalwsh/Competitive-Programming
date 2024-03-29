int n;
int arr[N];
int CountSubArrayDivision(int k){
    map<int,int>mp;
    int sum = 0;
    mp[sum] = 1;
    for(int i=0;i<n;i++){
        sum+=arr[i];
        mp[add(sum,0,k)]++;
    }
    int res = 0;
    for(auto &val:mp){
        res += val.second * (val.second - 1) / 2;
    }
    return res;
}