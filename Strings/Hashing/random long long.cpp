long long randomLongLong(long long l, long long r) {
    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}