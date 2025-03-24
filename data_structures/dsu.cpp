struct DSU {
    veci par, sz;
    int n;
    vector<pair<int, pii>> st;

    void rollback(int t) {
		while(sz(st) > t) {
            if(st.back().f) sz[st.back().s.f] = sz[st.back().s.s];
            else par[st.back().s.f] = st.back().s.s;
        }
	}

    DSU(int _n) {
        n = _n;
        par.resize(n + 1);
        sz.resize(n + 1, 1);
        for(int i = 1; i <= n; ++i) par[i] = i, sz[i] = 1;
    }
    
    int get(int v) {
        return par[v] = ( v == par[v] ? v : get(par[v]));
    }

    bool unite(int v, int u) {
        v = get(v), u = get(u);
        if(v == u) return false;
        if(sz[v] > sz[u]) swap(v, u);
        st.pb({1, {u, sz[u]}});
        st.pb({0, {v, par[v]}});
        par[v] = u;
        sz[u] += sz[v];
        return true;
    }
};