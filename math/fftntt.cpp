const int MOD = 998244353;
const int G = 3;
int modpow(int a, int e = MOD - 2) {
    long long r = 1, x = a;
    while (e) {
        if (e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return r;
}
void ntt(veci &a, bool invert) {
    int n = a.size(), j = 0;
    for (int i = 1; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = modpow(G, (MOD - 1) / len);
        if (invert) wlen = modpow(wlen);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int k = 0; k < len / 2; k++) {
                int u = a[i + k], v = a[i + k + len / 2] * w % MOD;
                a[i + k] = u + v < MOD ? u + v : u + v - MOD;
                a[i + k + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = modpow(n);
        for (int &x : a) x = 1LL * x * inv_n % MOD;
    }
}
veci multiply_mod(veci a, veci b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, true);
    return a;
}
void fft(vector<complex<ld>> &a, bool invert) {
    int n = a.size(), j = 0;
    for (int i = 1; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        complex<ld> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<ld> w(1);
            for (int k = 0; k < len / 2; k++) {
                complex<ld> u = a[i + k], v = a[i + k + len / 2] * w;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; i++) a[i] /= n;
}
vecll multiply(const vecll &a, const vecll &b) {
    vector<complex<ld>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vecll res(n);
    for (int i = 0; i < n; i++) res[i] = (long long)(fa[i].real() + 0.5);
    return res;
}
