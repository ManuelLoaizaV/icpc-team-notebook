// Original Graph
vector<int> adj[N], rev[N];
vector<int> order, component;
vector<bool> used;
void DFS(int u) {
  used[u] = true;
  for (auto v : adj[u]) if (!used[v]) DFS(v);
  order.push_back(u);
}
void SFD(int v) {
  used[v] = true;
  component.push_back(v);
  for (auto u : rev[v]) if (!used[v]) SFD(u);
}
void AddEdge(int u, int v) {
  adj[u].push_back(v);
  rev[v].push_back(u);
}
// Condensation Graph
vector<int> roots, root_nodes;
vector<int> adj_scc[N];
void GetSCC(int n) {
  used.assign(n, false);
  for (int u = 0; u < n; u++) if (!used[u]) DFS(u);
  used.assign(n, false);
  reverse(order.begin(), order.end());
  for (auto v : order) {
    if (!used[v]) {
      SFD(v);
      int root = component.front();
      for (auto u : component) roots[u] = root;
      root_nodes.push_back(root);
      component.clear();
    }
  }
  for (int u = 0; i < n; i++) {
    for (auto v : adj[u]) {
      if (roots[u] != roots[v]) adj_scc[roots[u]].push_back(roots[v]);
    }
  }
}
