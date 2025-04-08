// given tree with n nodes, and q queries of type:
// 1. get max sum of any subpath between a and b
// 2. assign c to all nodes' values in path between a and b

const int LOGN = 20;

int n;
int nxt[MAXN];
int sz[MAXN];
int up[MAXN][LOGN];
int tin[MAXN], tout[MAXN], tmr;
veci g[MAXN];
ll a[MAXN];

struct node {
    ll prefsum = 0, sufsum = 0, sum = 0, ans = 0;
    node(ll _sum = 0, ll _prefsum = 0, ll _sufsum = 0, ll _ans = 0) {
        sum = _sum;
        prefsum = _prefsum;
        sufsum = _sufsum;
        ans = _ans;
    }
} t[MAXN << 2];
ll u[MAXN << 2];

node operator + (const node &l, const node &r) {
    node res;
    res.sum = l.sum + r.sum;
    res.prefsum = max (l.prefsum, l.sum + r.prefsum);
    res.sufsum = max (r.sufsum, r.sum + l.sufsum);
    res.ans = max (max (l.ans, r.ans), l.sufsum + r.prefsum);
    return res;
}

const node NEUTRAL = node(0, 0, 0, 0);

/// removes edges v->parent[v], after this dfs there will be only edges parent[v]->v
void dfs_prepare(int v = 1, int p = 0) {
    if(v != 1) {
        int ind = -1;
        for(int i = 0; i < sz(g[v]); ++i) if(g[v][i] == p) ind = i;
        assert(ind != -1);
        g[v].erase(g[v].begin() + ind);
    }
    for(auto to : g[v]) dfs_prepare(to, v);
}

void dfs_sz(int v = 1) {
    sz[v] = 1;
    for(int i = 1; i <= 18; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for(auto &to : g[v]) {
        up[to][0] = v;
        dfs_sz(to);
        sz[v] += sz[to];
        if(sz[to] > sz[g[v][0]]) swap(to, g[v][0]);
    }
}

void dfs_hld(int v = 1) {
    tin[v] = ++tmr;
    for(auto to : g[v]) {
        nxt[to] = (to == g[v][0] ? nxt[v] : to);
        dfs_hld(to);
    }
    tout[v] = tmr;
}

bool upper(int v, int u) {
    return (tin[v] <= tin[u] && tout[v] >= tout[u]);
}

int get_lca(int a, int b) {
    if(upper(a, b)) return a;
    if(upper(b, a)) return b;
    for(int i = 18; i >= 0; --i)
        if(up[a][i] && !upper(up[a][i], b))
            a = up[a][i];
    return up[a][0];
}

void apply(int v, int len, ll val) {
    u[v] = val;
    val *= len;
    t[v].sum = val;
    t[v].ans = max(0ll, val);
    t[v].prefsum = t[v].sufsum = max(0ll, val);
}

void push(int v, int tl, int tr) {
    if(u[v] != -1e9) {
        int tm = tl + tr >> 1;
        apply(v << 1, (tm - tl + 1), u[v]);
        apply(v << 1 | 1, (tr - tm), u[v]);
        u[v] = -1e9;
    }
}

void upd_segment(int l, int r, ll val, int v = 1, int tl = 1, int tr = n) {
    if(l <= tl && tr <= r) {
        apply(v, (tr - tl + 1), val);
        return;
    }
    if(l > tr || r < tl) return;
    push(v, tl, tr);
    int tm = tl + tr >> 1;
    upd_segment(l, r, val, v << 1, tl, tm);
    upd_segment(l, r, val, v << 1 | 1, tm + 1, tr);
    t[v] = t[v << 1] + t[v << 1 | 1];
}

node getmaxsum(int l, int r, int v = 1, int tl = 1, int tr = n) {
    if(l <= tl && tr <= r) return t[v];
    if(l > tr || r < tl) return NEUTRAL;
    push(v, tl, tr);
    int tm = tl + tr >> 1;
    return getmaxsum(l, r, v << 1, tl, tm) + getmaxsum(l, r, v << 1 | 1, tm + 1, tr);
}

void upd_vertical(int a, int lca, ll val) {
    while(1) {
        if(nxt[a] == nxt[lca]) {
            upd_segment(tin[lca], tin[a], val);
            break;
        }
        upd_segment(tin[nxt[a]], tin[a], val);
        a = up[nxt[a]][0];
    }
}

void upd_path(int a, int b, ll val) {
    int lca = get_lca(a, b);
    upd_vertical(a, lca, val);
    upd_vertical(b, lca, val);
}

node get_vertical(int a, int lca) {
    node res = NEUTRAL;
    node tmp;
    while(1) {
        if(nxt[a] == nxt[lca]) {
            tmp = getmaxsum(tin[lca], tin[a]);
            swap(tmp.prefsum, tmp.sufsum);
            res = res + tmp;
            break;
        }
        tmp = getmaxsum(tin[nxt[a]], tin[a]);
        swap(tmp.prefsum, tmp.sufsum);
        res = res + tmp;
        a = up[nxt[a]][0];
    }
    return res;
}

ll get_ans(int a, int b) {
    if(tin[a] > tin[b]) swap(a, b);
    if(upper(a, b)) return get_vertical(b, a).ans;
    int lca = get_lca(a, b);
    node res = get_vertical(a, lca);
    vector <pii> pathes;
    a = b;
    while(1) {
        if(nxt[a] == nxt[lca]) {
            if(tin[lca] + 1 <= tin[a]) pathes.pb(mp(tin[lca] + 1, tin[a]));
            break;
        }
        pathes.pb(mp(tin[nxt[a]], tin[a]));
        a = up[nxt[a]][0];
    }
    reverse(all(pathes));
    for(auto it : pathes) res = res + getmaxsum(it.f, it.s);
    return res.ans;
}

void solve() {
    for(int i = 0; i < MAXN * 4; ++i) u[i] = -1e9;
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 2; i <= n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs_prepare();
    dfs_sz();
    nxt[1] = 1;
    dfs_hld();
    for(int i = 1; i <= n; ++i) upd_segment(tin[i], tin[i], a[i]);
    int q;
    cin >> q;
    for(int cs = 1; cs <= q; ++cs) {
        char type;
        int a, b;
        cin >> type >> a >> b;
        if(type == '2') {
            ll c;
            cin >> c;
            upd_path(a, b, c);
        } else cout << get_ans(a, b) << '\n';
    }
}