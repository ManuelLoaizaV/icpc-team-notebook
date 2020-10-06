const int INF = 1e9;
const int N = 1e5;
vector<pair<int, int>> adj[N];
int d[N];
void BFS_01(int s) {
  deque<pair<int, int>> q;
  for (int i = 0; i < N; i++) d[i] = INF;
  q.push_back({s, 0});
  d[s] = 0;
  while (q.size()) {
    int u = q.front().first;
    int cost = q.front().second;
    q.pop_front();
    if (d[u] != cost) continue;
    for (pair<int, int> e : adj[u]) {
      int v = e.first;
      int w = e.second;
      if (w + d[u] < d[v]) {
        d[v] = w + d[u];
        if (w == 0) q.push_front({v, d[v]});
        else q.push_back({v, d[v]});
      }
    }
  }
}
