int derangement(int n){
    if(n<=2){
        return n!=1;
    }
    return (n-1)*(derangement(n-1)+ derangement(n-2));
}