const int INF = 1e9;
const int N = 1e5;
vector<pair<int, int>> adj[N];
vector<int> d[N];
void Dijkstra(int s) {
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  q.push({0, s});  // Al nodo s se llega con distancia 0
  while (q.size()) {
    int u = q.top().second;
    int w = q.top().first;
    q.pop();
    // Verificar que este no es el mejor de llegar a u
    if (d[u] != w) continue;
    // la arista pertenece al dijkstra tree u w
    for (pair<int, int> e : adj[u]) {
      int v = e.first;
      int nw = w + e.second;
      // Relajamos sus vecinos
      if (nw < d[v]) {
        d[v] = nw;
        q.push({d[v], v});
      }
    }
  }
}
