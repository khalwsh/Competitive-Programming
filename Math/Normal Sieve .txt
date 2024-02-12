bool Prime[N];
void sieve() {
    for(int i=2;i<N;i++){
        Prime[i]=true;
    }
    for (int i = 2; i*i < N; i++) {
        if(Prime[i]) {
            for (int j = i * i; j < N; j += i) {
                Prime[j] = false;
            }
        }
    }
}