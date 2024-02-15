bool isPowerOfTwo(unsigned int n) {
    return n && !(n & (n - 1));
}