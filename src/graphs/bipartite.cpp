// Checks if a graph G = (V, E) is bipartite and partitions components.
// A graph is bipartite iff it contains no odd-length cycles.
struct Bipartite {
  struct Neighbor {
    int node, index;
    Neighbor() {}
    Neighbor(int _node, int _index) : node(_node), index(_index) {}
  };
  struct Edge {
    int from, to;
    Edge() {}
    Edge(int _from, int _to) : from(_from), to(_to) {}
  };
  int V, E;
  vector<vector<Neighbor>> adj;
  vector<Edge> edges;
  vector<bool> visited;
  vector<int> depth;
  Bipartite(int _V = -1) {
    if (_V >= 0)
      Init(_V);
  }
  void Init(int _V) {
    V = _V;
    E = 0;
    adj.assign(V, {});
    edges.clear();
  }
  void AddEdge(int from, int to) {
    adj[from].emplace_back(to, E);
    adj[to].emplace_back(from, E);
    edges.emplace_back(from, to);
    E++;
  }

  vector<array<vector<int>, 2>> components;
  // Returns true if the component is bipartite and
  // stores nodes partitioned by side for the component.
  bool DFS(int node, int parent) {
    assert(!visited[node]);
    visited[node] = true;
    depth[node] = parent < 0 ? 0 : depth[parent] + 1;
    components.back()[depth[node] % 2].push_back(node);
    bool is_bipartite = true;
    for (Neighbor &neighbor : adj[node]) {
      if (neighbor.node == parent)
        continue;
      if (!visited[neighbor.node] && !DFS(neighbor.node, node))
        is_bipartite = false;
      if (depth[node] % 2 == depth[neighbor.node] % 2)
        is_bipartite = false;
    }
    return is_bipartite;
  }

  // Returns true if the entire graph is bipartite.
  // Time complexity: O(V + E).
  bool Compute(void) {
    depth.assign(V, -1);
    visited.assign(V, false);
    components.clear();
    bool is_bipartite{true};
    for (int node = 0; node < V; node++) {
      if (!visited[node]) {
        components.emplace_back();
        if (!DFS(node, -1))
          is_bipartite = false;
      }
    }
    return is_bipartite;
  }
};