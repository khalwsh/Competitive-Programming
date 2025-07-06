bool Ncr(int n , int i) {
    // Ncr(n , i) % 2 = 1 if every bit of i is less than or equal to the corresponding bit of n
    return !(i & ~(n - 1));
}