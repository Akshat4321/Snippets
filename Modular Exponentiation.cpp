long long binpow(long long a, long long b , long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b %2 ==1) res = res * a % mod;

        a = a * a %mod;
        b = b/ 2;
    }
    return res;
}
