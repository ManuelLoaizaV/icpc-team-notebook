const int N = 1e4 + 5;
vector<int> adj[N];
int timer, depth[N], in[N], out[N], anc[N][32 - __builtin_clz(N)];
void DFS(int u) {
  in[u] = timer++;
  for (int v : adj[u]) {
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      DFS(v);
    }
  }
  out[u] = timer++;
}
void Precalculate(int n, int root = 0) {
  anc[root][0] = -1;
  depth[root] = 0;
  timer = 0;
  DFS(root);
  for (int j = 1; (1 << j) < n; j++) {
    for (int i = 0; i < n; i++) {
      if (anc[i][j - 1] != -1) {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
      } else {
        anc[i][j] = -1;
      }
    }
  }
}
bool IsAncestor(int u, int v) { return (in[u] <= in[v] && out[u] >= out[v]); }
int LCA(int u, int v) {
  if (IsAncestor(u, v)) return u;
  int bits = 31 - __builtin_clz(depth[u]);
  for (int i = bits; i >= 0; i--)
    if (anc[u][i] != -1 && !IsAncestor(anc[u][i], v)) u = anc[u][i];
  return anc[u][0];
}
