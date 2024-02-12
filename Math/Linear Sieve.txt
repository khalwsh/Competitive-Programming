int Lpf[N];
vector<int>LinearSieve(){
    for(int i=1;i<N;i++)Lpf[i]=i;
    vector<int>primes;
    for(int i=2 ;i<N;i++){
        if(Lpf[i]==i){
            primes.emplace_back(i);
        }
        for(auto &val:primes){
            if(i*val>=N)break;
            Lpf[i*val] = val;
        }
    }
    return primes;
}