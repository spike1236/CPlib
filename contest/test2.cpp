#include <bits/stdc++.h>
#define sz(_v) ((int)((_v).size()))
#define all(_v) ((_v).begin(), (_v).end())
#define pb push_back
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

// template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(forward<T>(fun)) {}
    
    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using veci = vector<int>;
using vecll = vector<ll>;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const double PI = 3.1415926535;
const double eps = 1e-9;
const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;
const int MAXN = 2e5 + 10;
const int INF = 1e9;
const ll LLINF = 1e18;

// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rnd64(chrono::steady_clock::now().time_since_epoch().count());
int64_t now() {
    chrono::milliseconds ms = duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

struct Solution {
    void read() {
    }
  
    void solve(stringstream& out) {
    }
};

const int MAXTHREADS = 8;
const int MAXTESTS = 1e5 + 10;

stringstream out[MAXTESTS];
mutex mut;
int cur, CNT_TESTS;
thread threads[MAXTHREADS];

void solutionRunner() {
    while (true) {
        Solution s;
        int id;
        mut.lock();
        if (cur >= CNT_TESTS) {
            mut.unlock();
            return;
        }
        id = cur;
        cur++;
        s.read();
        mut.unlock();
        s.solve(out[id]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> CNT_TESTS;
    for (int i = 0; i < MAXTHREADS; i++) {
        threads[i] = thread(solutionRunner);
    }
    for (int i = 0; i < MAXTHREADS; i++) {
        threads[i].join();
    }
    for (int i = 0; i < CNT_TESTS; i++) {
        // cout << "Case #" << i + 1 << ": " << '\n';
        cout << out[i].str() << '\n';
    }
    return 0;
}