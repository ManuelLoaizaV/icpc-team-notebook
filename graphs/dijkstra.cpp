const int INF = 1e9;
const int N = 1e5;
vector<pair<int, int>> adj[N];
vector<int> d[N];
void Dijkstra(int s) {
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  q.push({0, s});
  while (!q.empty()) {
    pair<int, int> path = q.top();
    int u = path.second;
    q.pop();
    if (d[u] != path.first) continue;
    for (auto e : adj[u]) {
      int v = e.first, w = e.second;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
}
