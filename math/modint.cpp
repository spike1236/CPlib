const int mod = 1000000007;

constexpr int calculate_phi(int n) {
    if(n == 998244353 || n == 1000000007) return n - 1;
    int ans = n;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            ans /= i; ans *= i - 1; while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans /= n, ans *= n - 1;
    return ans;
}
 
constexpr int phi_minus_one = calculate_phi(mod) - 1;
 
class Mint {
public:
    int x;
 
public:
    void norm() {
        x %= mod;
        if(x < 0) x += mod;
    }
    Mint(int a, bool small) {
        x = a;
        if(x >= mod) x -= mod;
        if(x < 0) x += mod;
    }
    Mint() { x = 0; }
    Mint(long long a) {
        if(a >= mod || a <= -mod) a %= mod;
        x = a;
        if(x < 0) x += mod;
    }
    Mint(const Mint &b) { x = b.x; }
    friend ostream &operator <<(ostream &out, const Mint &a) { out << a.x; return out; }
    friend istream &operator >>(istream &in, Mint &a) { in >> a.x; return in; }
    Mint operator +(const Mint &b) const & {
        return Mint(x + b.x, 1);
    }
    Mint operator +(int a) const & {
        return Mint(x + a, 1);
    }
    Mint operator -(const Mint &b) const & {
        return Mint(x - b.x, 1);
    }
    Mint operator -(int a) const & {
        return Mint(x - a, 1);
    }
    friend Mint operator -(const Mint &a) {
        return Mint(mod - a);
    }
    Mint operator *(const Mint &b) const & {
         return Mint(1LL * x * b.x);
    }
    Mint operator *(int a) const & {
        return Mint(1LL * x * a);
    }
    Mint &operator +=(const Mint &b) {
        x += b.x;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator +=(int a) {
        x += a;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator -=(const Mint &b) {
        x += mod - b.x;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator -=(int a) {
        x += mod - a;
        if(x >= mod) x -= mod;
        return *this;
    }
    Mint &operator *=(const Mint &b) {
        x = (long long) x * b.x % mod;
        return *this;
    }
    Mint &operator *=(int a) {
        x = (long long) x * a % mod;
        return *this;
    }
    Mint &operator /=(const Mint &b) {
        x = (long long) x * b.inv().x % mod;
        return *this;
    }
    Mint &operator /=(int a) {
        x = (long long) x * Mint(a, 1).inv().x % mod;
        return *this;
    }
    Mint bpow(long long n) const & {
        Mint a(x);
        Mint ans(1);
        while(n) {
            if(n & 1) ans *= a;
            n >>= 1;
            a *= a;
        }
        return ans;
    }
    Mint inv() const & {
        return bpow(phi_minus_one);
    }
    Mint operator /(const Mint &b) const & {
        return b.inv() * x;
    }
    Mint operator /(int a) const & {
        return Mint(a, 1).inv() * x;
    }
    friend Mint operator -(int a, const Mint &b) {
        Mint res(b - a);
        res.x = mod - res.x;
        if(res.x == mod) res.x = 0;
        return res;
    }
    friend Mint operator +(int a, const Mint &b) {
        return Mint(b + a);
    }
    friend Mint operator *(int a, const Mint &b) {
        return Mint(b * a);
    }
    friend Mint operator /(int a, const Mint &b) {
        return Mint(a, 1) * b.inv();
    }
    Mint &operator=(const Mint &b) {
        x = b.x;
        return *this;
    }
    bool operator==(int a) const & {
        return (x == a);
    }
    bool operator!=(int a) const & {
        return (x != a);
    }
    bool operator==(const Mint &b) const & {
        return (x == b.x);
    }
    bool operator!=(const Mint &b) const & {
        return (x != b.x);
    }
    friend bool operator==(int a, const Mint &b) {
        return (b.x == a);
    }
    friend bool operator!=(int a, const Mint &b) {
        return (b.x != a);
    }
};