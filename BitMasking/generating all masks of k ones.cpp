
void GospersHack(int n,int k,function<void(int)>f){
    int sets=(1ll<<k)-1;
    int limit=(1ll<<n);
    while(sets<limit){
        f(sets);//handle set
        int c=sets&-sets;
        int r=sets+c;
        sets=(((r^sets)>>2)/c)|r;
    }
}