vector<long long>factorial(long long n,const long long& mod){vector<long long>v(n+1,1);for(int i=2;i<=n;i++)v[i]=mul(i,v[i-1],mod);return v;}


//this function take length and index return the permutation that in order of small to large it's index is nth

vector<int>get_nth_permutation(int len,int nth){
    ordered_set<int>v;
    for(int i=0;i<len;i++)
        v.insert(i+1);
    vector<int>res;
    nth--;
    vector<int>fact= factorial(len,INT64_MAX);
    for(int i=len-1;i>=0;i--){
        int p=nth/fact[i];
        res.emplace_back(*v.find_by_order(p));
        v.erase(v.find_by_order(p));
        nth%= fact[i];
    }
    return res;
}

//this function uses the old function it solve the following given a permutation what is it's index in order of small to large

int permutation_in_order(vector<int>&v){
    int len=(int)v.size();
    vector<int>fact= factorial(len,INT64_MAX);
    int left=1,right=fact[len];
    while(left<=right){
        int mid=left+(right-left)/2;
        vector<int>temp= get_nth_permutation(len,mid);
        if(temp==v)return mid;
        else if(temp>v)right=mid-1;
        else left=mid+1;
    }
    return -1;
}

//if there is a permutation or string that is applied to some funtion that change it's order then the permutation or the string will return 

//to it's orginal state after n where n is the lcm of the length of the cycles in the operations

//inclusion exclusion princible : process all subset if odd inculde it else exclude it