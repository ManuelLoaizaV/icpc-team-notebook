#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

const int N = 1e4 + 1;
int prev_n = 0;
vector<int> adj[N], cost[N];

struct SegmentTree {
	int tree[4 * N];
	
	void build(vector<int> &a, int id, int tl, int tr) {
		if (tl == tr) {
			tree[id] = a[tl];
		} else {
			int tm = (tl + tr) / 2;
			build(a, 2 * id, tl, tm);
			build(a, 2 * id + 1, tm + 1, tr);
			tree[id] = max(tree[2 * id], tree[2 * id + 1]);
		}
	}
	
	void update(int pos, int val, int id, int tl, int tr) {
		if (tl == tr) {
			tree[id] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) update(pos, val, 2 * id, tl, tm);
			else update(pos, val, 2 * id + 1, tm + 1, tr);
			tree[id] = max(tree[2 * id], tree[2 * id + 1]);
		}
	}
	
	int query(int l, int r, int id, int tl, int tr) {
		if (l <= tl and tr <= r) return tree[id];
		int tm = (tl + tr) / 2;
		if (r <= tm) return query(l, r, 2 * id, tl, tm);
		if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
		return max(query(l, r, 2 * id, tl, tm), query(l, r, 2 * id + 1, tm + 1, tr));
	}
};

struct HLD {
	SegmentTree st;
	int n, global_id;
	int parent[N], depth[N], tree_size[N], id[N], rt[N];

	int make_size(int u, int pu = -1, int d = 0) {
		parent[u] = pu;
		depth[u] = d;
		tree_size[u] = 1;
		for (int v : adj[u]) {
			if (v != pu) tree_size[u] += make_size(v, u, d + 1);
		}
		return tree_size[u];
	}

	void DFS(int u, int root = -1) {
		id[u] = global_id;
		global_id++;
		rt[u] = root;
		int w = 0;
		int w_size = -1;
		for (int v : adj[u]) {
			if (v != parent[u] and tree_size[v] > w_size) {
				w = v;
				w_size = tree_size[v];
			}
		}
		if (w) DFS(w, root);
		for (int v : adj[u]) if (v != parent[u] and v != w) DFS(v, v);
	}

	void modify(int u, int val) {
		st.update(id[u], val, 1, 0, n - 1);
	}

	int query(int u, int v) {
		int ans = 0;
		while (rt[u] != rt[v]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			ans = max(ans, st.query(id[rt[v]], id[v], 1, 0, n - 1));
			v = parent[rt[v]];
		}
		int a = id[u];
		int b = id[v];
		if (a > b) swap(a, b);
		ans = max(ans, st.query(a, b, 1, 0, n - 1));
		return ans;
	}

	void build(int _n) {
		n = _n;
		global_id = 0;
		make_size(0);
		DFS(0);
		vector<int> a(n, 0);
		for (int u = 0; u < n; u++) {
			int sz = adj[u].size();
			for (int i = 0; i < sz; i++) {
				int v = adj[u][i];
				int x = u;
				int y = v;
				if (depth[x] > depth[y]) swap(x, y);
				a[id[y]] = cost[u][i];
			}
		}
		a[0] = 0;
		st.build(a, 1, 0, n - 1);
	}
} hld;

void solve() {
	for (int i = 0; i < prev_n; i++) {
		adj[i].clear();
		cost[i].clear();
	}
	int n;
	cin >> n;
	vector<pair<int, int>> edges;
	for (int i = 0; i < n - 1; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		u--;
		v--;
		edges.push_back({u, v});
		adj[u].push_back(v);
		adj[v].push_back(u);
		cost[u].push_back(c);
		cost[v].push_back(c);
	}
	hld.build(n);
	string s;
	while (true) {
		cin >> s;
		if (s[0] == 'C') {
			int i, c;
			cin >> i >> c;
			i--;
			int u = edges[i].first;
			int v = edges[i].second;
			if (hld.depth[u] > hld.depth[v]) swap(u, v);
			hld.modify(v, c);
		}
		if (s[0] == 'Q') {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			if (u == v) cout << 0 << endl;
			else cout << hld.query(u, v) << endl;
		}
		if (s[0] == 'D') break;
	}
	prev_n = n;
}

int main() {
	fastio;
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
