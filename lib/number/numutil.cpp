#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class NumUtil {
    public:
    static int gcd(int a, int b) {
        return (a < b) ? gcd(b, a) : (b > 0) ? gcd(b, a % b) : a;
    }

    static int lcm(int a, int b) { return a / gcd(a, b) * b; }

    static ll gcd(ll a, ll b) {
        return (a < b) ? gcd(b, a) : (b > 0) ? gcd(b, a % b) : a;
    }

    static ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
};