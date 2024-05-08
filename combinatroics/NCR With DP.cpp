int NCR(int a , int b){
    // you should apply dp
    if(a < b)return 0;
    if(b == 0 || a == b)return 1;
    if(b > a - b)b = a - b;
    return NCR(a - 1 , b - 1) + NCR(a - 1, b);
}