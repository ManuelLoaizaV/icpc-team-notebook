const int N = 1e4;
vector<int> adj[N], cost[N];
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
		vector<int> a(n, 0);// modificar dependiendo del problema
		st.build(a, 1, 0, n - 1);
	}
} hld;
