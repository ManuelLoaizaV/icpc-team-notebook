const int N = 1e5;
vector<int> adj[N];
int V, color[N], d[N], p[N];

// O(V + E)
void BFS(int s) {
	for (int i = 0; i < V; i++) {
		color[i] = 0;
		d[i] = INF;
		p[i] = -1;
	}
	color[s] = 1;
	d[s] = 0;
	p[s] = -1;
	queue<int> q;
	q.push(s);
	while (not q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : adj[u]) {
			if (color[v] == 0) {
				color[v] = 1;
				d[v] = d[u] + 1;
				p[v] = u;
				q.push(v);
			}
		}
		color[u] = 2;
	}
}

// Prints out the vertices on a shortest path from s to v
void print_path(int s, int v) {
	if (v == s) cout << s << endl;
	else {
		if (p[v] == -1) cout << "no path from " << s << " to " << v << " exists" << endl;
		else { 
			print_path(s, p[v]);
			cout << v << endl;
		}
	}
}