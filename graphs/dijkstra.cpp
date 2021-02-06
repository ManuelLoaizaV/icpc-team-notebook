const int INF = 1e9;
const int N = 1e5;
vector<Pair> adj[N];
Long d[N];
void Dijkstra(int s) {
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = 0;
  priority_queue<Pair, vector<Pair>, greater<Pair>> q;
  q.push({0, s});
  while (!q.empty()) {
    Pair path = q.top();
    int u = path.second;
    q.pop();
    if (d[u] != path.first) continue;
    for (Pair e : adj[u]) {
      int v = e.first; Long w = e.second;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
}
