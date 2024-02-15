int inv[N];
void ModInverse(int m){
//calculating the mod inverse for range [1,m-1] under module mod
    inv[1] = 1;
    for(int a = 2; a < m; ++a)
        inv[a] = mod - (long long)(mod/a) * inv[mod%a] % mod;
}