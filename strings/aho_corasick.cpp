// Given a text s and a set of strings t, for each string t_i, check if t_i is a substring of s.

const int MAXN = 1e6 + 10;
const int C = 26;
int sz = 1;
bool up[MAXN];
int link[MAXN];
map <int, veci> term;
map <int, int> to[MAXN], go[MAXN];
veci ord, terminal;

void add_string(string s, int idx) {
    int v = 1;
    for(auto _c : s) {
        unsigned int c = _c - 'a';
        if(!to[v].count(c)) to[v][c] = ++sz;
        v = to[v][c];
    }
    if(!term.count(v)) terminal.pb(v);
    term[v].pb(idx);
}

void build() {
    for(int i = 0; i < C; ++i) to[0][i] = 1, go[1][i] = 1;
    queue <int> q;
    for(auto i : to[1]) {
        int u = i.s;
        link[u] = 1;
        q.push(u);
    }
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        ord.pb(v);
        for(int i = 0; i < C; ++i) {
            if(to[link[v]].count(i)) go[v][i] = to[link[v]][i];
            else go[v][i] = go[link[v]][i];
            if(to[v].count(i)) {
                link[to[v][i]] = go[v][i];
                q.push(to[v][i]);
            }
        }
    }
}

void solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        string v;
        cin >> v;
        add_string(v, i);
    }
    build();
    reverse(all(ord));
    int v = 1;
    for(auto _c : s) {
        int c = _c - 'a';
        if(to[v].count(c)) v = to[v][c];
        else v = go[v][c];
        up[v] = 1;
    }
    for(auto it : ord)
        up[link[it]] |= up[it];
    int ans[n];
    for(auto it : terminal)
        for(auto j : term[it]) ans[j - 1] = up[it];
    for(int i = 0; i < n; ++i) cout << (ans[i] ? "Yes" : "No") << '\n';
}
