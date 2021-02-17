const Long INF = 1e18;
const int N = 1e5;
vector<Pair> adj[N];
Long d[N];
void BFS_01(int s) {
  deque<Pair> q;
  for (int i = 0; i < N; i++) d[i] = INF;
  q.push_back({s, 0});
  d[s] = 0;
  while (q.size()) {
    int u = q.front().first;
    Long cost = q.front().second;
    q.pop_front();
    if (d[u] != cost) continue;
    for (Pair e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if (w + d[u] < d[v]) {
        d[v] = w + d[u];
        if (w == 0) {
          q.push_front({v, d[v]});
        } else {
          q.push_back({v, d[v]});
        }
      }
    }
  }
}
