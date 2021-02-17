const int N = 1e3;
const Long INF = 1e18;
Long d[N][N];
void AddEdge(int u, int v, int w) {
  if (w < d[u][v]) {
    d[u][v] = w;
    p[u][v] = u;
  }
}
vector<int> GetPath(int u, int v) {
  if (d[u][v] == INF) return {};
  vector<int> path;
  while (v != -1) {
    path.push_back(v);
    v = parent[u][v];
  }
  reverse(path.begin(), path.end());
  return path;
}
vector<int> GetNegativeCycle(int u, int v, int n) {
  for (int i = 0; i < n; i++) v = p[u][v];
  vector<int> cycle = {v};
  v = p[u][v];
  while (v != cycle[0]) {
    cycle.push_back(v);
    v = p[u][v];
  }
  return cycle;
}
void FloydWarshall (int n){
  for (int u = 0; u < n; u++) {
    for (int v = 0; v < n; v++) {
      d[u][v] = INF;
      p[u][v] = -1;
    }
    d[u][u] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++) {
        if (d[u][k] == INF || d[k][v] == INF) continue;
        if (d[u][k] + d[k][v] < d[u][v]) {
          d[u][v] = max(-INF, d[u][k] + d[k][v]);
          p[u][v] = p[k][v];
        }
      }
    }
  }
  for (int u = 0; u < n; u++) {
    for (int v = 0; v < n; v++) {
      for (int x = 0; x < n; x++) {
        if (d[x][x] < 0 && d[u][x] != INF && d[x][v] != INF) d[u][v] = -INF;
      }
    }
  }
}
