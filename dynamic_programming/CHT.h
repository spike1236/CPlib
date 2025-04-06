struct line {
    ll k = 0, b = 0;
    line() {
        k = 0;
        b = 0;
    }
    line(ll _k, ll _b) {
        k = _k;
        b = _b;
    }
    ll getY(ll x) {
        return k * x + b;
    }
};

ld cross(const line &a, const line &b) {
    return ((ld)(b.b - a.b)) / (a.k - b.k);
}

struct CHT {
    vector<line> lines;
    CHT() { lines = vector<line>{}; }
    void add(const line &l) {
        if(sz(lines) && l.k == lines.back().k) {
            if(l.b < lines.back().b) lines.pop_back();
            else return;
        }
        while(sz(lines) > 1 && cross(lines.back(), l) <= cross(lines[sz(lines) - 2], lines.back())) lines.pop_back();
        lines.pb(l);
    }

    ll get(ll x) {
        if(lines.empty()) return 0;
        int l = 0, r = lines.size() - 2, re = lines.size() - 1;
        while(l <= r) {
            int m = l + r >> 1;
            if(lines[m].getY(x) < lines[m + 1].getY(x)) re = m, r = m - 1;
            else l = m + 1;
        }
        return lines[re].getY(x);
    }
}