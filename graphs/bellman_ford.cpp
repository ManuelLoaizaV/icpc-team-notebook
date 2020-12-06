bool BellmanFord(int s, int n) {
  for (int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;
  bool has_relaxed;
  for (int i = 0; i < n; i++) {
    has_relaxed = false;
    for (Edge e : edges) {
      int u = e.u, v = e.v, w = e.w;
      if (d[u] != INF && d[u] + w < d[v]) {
        has_relaxed = true;
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
    if (!has_relaxed) break;
  }
  return has_relaxed;
}
