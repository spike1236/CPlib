bool used[MAXN];
int tin[MAXN], fup[MAXN], tmr;

void dfs(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = tmr++;
	for (auto to : g[v]) {
		if (to == p)  continue;
		if (used[to]) {
			fup[v] = min(fup[v], tin[to]);
		} else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				cout << "! " << v << ' ' << to << '\n';
		}
	}
}