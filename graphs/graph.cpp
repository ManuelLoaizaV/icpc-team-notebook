const int INF = 1e9;
const int N = 1e5;
struct Graph {
  vector<int> adj[N];
  bool is_used[N];
  int in[N], out[N], timer;  // DFS
  int d[N];  // BFS
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      is_used[i] = false;
      in[i] = out[i] = 0;
    }
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void BFS(int s, int n) {
    for (int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    deque<int> tour;
    tour.push_back(s);
    while (!tour.empty()) {
      int u = tour.front();
      tour.pop_front();
      for (int v : adj[u]) {
        if (d[v] == INF) {
          d[v] = d[u] + 1;
          tour.push_back(v);
        }
      }
    }
  }
  void DFS(int u) {
    is_used[u] = true;
    in[u] = ++timer;
    for (int v : adj[u]) if (!is_used[v]) DFS(v);
    out[u] = ++timer;
  }
} g;
