int d[MAXN][2];
char a[MAXN];
int n;

void solve() {
    cin >> (a + 1);
    n = strlen(a + 1);
    ll ans = 0;
    for(int z = 0, l = 1, r = 1; z < 2; ++z, l = 1, r = 1) {
        for(int i = 1; i <= n; ++i) {
            if(i < r) d[i][z] = min(r - i + !z, d[l + r - i + !z][z]);
            int L = i - d[i][z], R = i + d[i][z] - !z;
            while(L - 1 > 0 && R + 1 <= n && a[L - 1] == a[R + 1]) L--, ++R, d[i][z]++;
            if(R > r) l = L, r = R;
            ans += d[i][z];
        }
    }
    cout << ans;
}