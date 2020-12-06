const int N = 5e3;
const int INF 1e9;
vector<pair<int, int>> adj[N];
int d[N], p[N];
void DFS(int u) {
  d[u] = -INF;
  for (auto e : adj[u]) if (d[e.first] != -INF) DFS(e.first);
}
bool BellmanFord(int s, int n) {
  for (int i = 0; i < n; i++) {
    d[i] = INF;
    p[i] = -1;
  }
  d[s] = 0;
  vector<bool> in_cycle(n, false);
  bool has_relaxed;
  for (int it = 0; it < n; it++) {
    has_relaxed = false;
    for (int u = 0; u < n; u++) {
      for (auto e : adj[u]) {
        int v = e.first, w = e.second;
        if (d[u] != INF && d[u] + w < d[v]) {
          d[v] = d[u] + w;
          p[v] = u;
          has_relaxed = true;
          if (it == n - 1) in_cycle[v] = true;
        }
      }
    }
    if (!has_relaxed) break;
  }
  for (int u = 0; u < n; u++) if (in_cycle[u] && d[u] != -INF) DFS(u);
  return has_relaxed;
}
vector<int> GetNegativeCycle(int u, int n) {
  for (int i = 0; i < n; i++) u = p[u];
  vector<int> cycle = {u};
  u = p[u];
  while (u != cycle[0]) {
    cycle.push_back(u);
    u = p[u];
  }
  return cycle;
}
vector<int> GetPath(int u) {
  if (d[u] == INF) return {};
  vector<int> path;
  while (u != -1) {
    path.push_back(u);
    u = p[u];
  }
  reverse(path.begin(), path.end());
  return path;
}
