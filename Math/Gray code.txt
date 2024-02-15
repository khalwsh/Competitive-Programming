int g (int n) {
    return n ^ (n >> 1);
//convert from decimal to gray
}

int rev_g (int g) {
  int n = 0;
//convert from gray to decimal
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
vector<string>GenerateGrayCodeKnownLength(int n){
    vector<string>ans;
    for(int i=0;i<(1<<n);i++){
        bitset<16>b = g(i);
        string temp ;
        for(int j=n-1;j>=0;j--){
            temp+= to_string(b[j]);
        }
        ans.emplace_back(temp);
    }
    return ans;
}
