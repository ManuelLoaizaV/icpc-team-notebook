const Long INF = 1e9;
const int N = 5e3;
vector<Pair> adj[N];
Long d[N];
int p[N];
void DFS(int u) {
  d[u] = -INF;
  for (auto e : adj[u]) if (d[e.first] != -INF) DFS(e.first);
}
bool SPFA(int s, int n) {
  for (int i = 0; i < n; i++) {
    d[i] = INF;
    p[i] = -1;
  }
  queue<int> q;
  vector<bool> in_queue(n, false);
  vector<int> cnt(n, 0);
  d[s] = 0;
  in_queue[s] = true;
  q.push(s);
  bool has_negative_cycle = false;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_queue[u] = false;
    cnt[u]++;
    if (cnt[u] >= n) {
      has_negative_cycle = true;
      break;
    }
    for (auto e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        p[v] = u;
        if (!in_queue[v]) {
          q.push(v);
          in_queue[v] = true;
        }
      }
    }
  }
  if (!has_negative_cycle) return false;
  vector<bool> in_cycle(n, false);
  for (int u = 0; u < n; u++) {
    for (auto e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if (d[u] != INF && d[u] + w < d[v]) in_cycle[v] = true;
    }
  }
  for (int u = 0; u < n; u++) if (in_cycle[u] && d[u] != -INF) DFS(u);
  return true;
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
