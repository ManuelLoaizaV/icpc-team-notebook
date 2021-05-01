const int N = 1e5;
bool is_art[N + 1];
int gid = 0, rch = 0, id[N], lo[N];
vector<int> adj[N];
vector<pair<int, int>> bridges;
void clear(int n) {
  bridges.clear();
  for(int i = 0; i <= n; ++i) {
    adj[i].clear();
    id[i] = lo[i] = 0;
    is_art[i] = 0;
  }
}
// Resetear rch = 0, gid = 1
// modifacion con aristas repetidas
// en vez de p = padre se usa pedge = arista de la que proviene y adj seria vector<pair<int, int>> adj;
void dfs(int from, int p = -1) {
  id[from] = lo[from] = ++gid;
  for(int to : adj[from]) {
    if (id[to] == 0) {
      if (p == -1) rch++;
      dfs(to, from);
      lo[from] = min(lo[from], lo[to]);
      if (lo[to] >= id[from]) is_art[from] = 1;
      if (lo[to] > id[from]) bridges.pb({from, to});
    } 
    else if (to != p) lo[from] = min(lo[from], id[to]);
  }
  if (p == -1) is_art[from] = (rch > 1);
}
