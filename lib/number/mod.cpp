#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class Mod {
    private:
    int mod;

    public:
    Mod(int n) { mod = n; }

    ll add(ll a, ll b) { return (a + b) % mod; }

    ll mul(ll a, ll b) { return (a * b) % mod; }

    ll pow(ll a, ll n) {
        ll ret;
        if (n == 0)
            ret = 1;
        else if (n == 1)
            ret = a;
        else {
            ll sq = pow(a, n / 2);
            ret = mul(sq, sq);
            if (n % 2 != 0) ret = mul(ret, a);
        }
        return ret % mod;
    }

    ll div(ll a, ll b) { return mul(a, pow(b, mod - 2)); }
};