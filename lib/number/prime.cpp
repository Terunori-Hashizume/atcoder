#include <bits/stdc++.h>
using namespace std;

class Prime {
    public:
    static map<int, int> prime_division(int n) {
        map<int, int> factors;
        for (int base = 2; base * base <= n; ++base) {
            int exp = 0;
            while (n % base == 0) {
                n /= base;
                exp++;
            }
            factors[base] = exp;
        }
        if (n > 1) factors[n] = 1;
        return factors;
    }

    static bool is_prime(int n) {
        for (int i = 2; i * i < n; ++i) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }
};