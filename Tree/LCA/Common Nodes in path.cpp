int common_in_path(int a, int b, int c , int d){
    return max(0 , 2 * (dist(a , b) + dist(c , d)) - dist(a , c) - dist(a , d) - dist(b , c) - dist(b , d)) / 2 + 1);
}
