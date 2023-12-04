struct Graph {
  int n_vertices, n_components;
  vector<vector<int>> adj, rev;
  vector<bool> visited;
  vector<int> order, scc;
  Graph(int n): n_vertices(n) {
    adj.resize(n_vertices);
    rev.resize(n_vertices);
    visited.resize(n_vertices, false);
    scc.resize(n_vertices, -1);
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    rev[v].push_back(u);
  }
  void ToposortDFS(int u) {
    visited[u] = true;
    for (int v : adj[u])
      if (!visited[v])
        ToposortDFS(v);
    order.push_back(u);
  }
  void SCCsDFS(int u) {
    scc[u] = n_components;
    for (int v : rev[u])
      if (scc[v] == -1)
        SCCsDFS(v);
  }
  void FindSCCs(void) {
    for (int u = 0; u < n_vertices; u++)
      if (!visited[u])
        ToposortDFS(u);
    reverse(order.begin(), order.end());
    for (int u : order) {
      if (scc[u] != -1) continue;
      SCCsDFS(u);
      n_components++;
    }
  }
  Graph BuildCondensation(void) {
    FindSCCs();
    Graph condensation(n_components);
    for (int u = 0; u < n_vertices; u++) {
      for (int v : adj[u]) {
        if (scc[u] == scc[v]) continue;
        condensation.AddEdge(scc[u], scc[v]);
      }
    }
    return condensation;
  }
};