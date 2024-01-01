const int N = 1e5;
struct DisjointSets {
  int parent[N];
  int size[N];
  void MakeSet(int u) {
    parent[u] = u;
    size[u] = 1;
  }
  void Build(int n) {
    for (int i = 0; i < n; i++) MakeSet(i);
  }
  int Find(int u) {
    if (parent[u] == u) return u;
    return (parent[u] = Find(parent[u]));
  }
  void Join(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u != v) {
      if (size[u] > size[v]) swap(u, v);
      parent[u] = v;
      size[v] += size[u];
    }
  }
  bool SameSet(int u, int v) { return Find(u) == Find(v); }
  int GetSize(int u) { return size[Find(u)]; }
};
