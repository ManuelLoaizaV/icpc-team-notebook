// https://cses.fi/problemset/task/2134/
#include <bits/stdc++.h>
using namespace std;

typedef int Long;

const int N = 2e5;

// Graph

vector<int> adj[N];

void AddEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

// Segment Tree

struct SegmentTree {
  int n;
  Long tree[4 * N];

  SegmentTree(void) {}

  SegmentTree(int n_) { n = n_; }

  Long Merge(const Long& x) { return x; }

  Long Merge(const Long& x, const Long& y) { return max(x, y); }

  void Build(const vector<Long>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Merge(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }

  void Build(const vector<Long>& a) { Build(a, 1, 0, n - 1); }

  void Update(int pos, Long val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Merge(val);
    } else {
      int tm = (tl + tr) / 2;
     if (pos <= tm) {
       Update(pos, val, 2 * id, tl, tm);
     } else {
       Update(pos, val, 2 * id + 1, tm + 1, tr);
     }
     tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }

  void Update(int pos, Long val) { Update(pos, val, 1, 0, n - 1); }

  Long Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }

  Long Query(int l, int r) { return Query(l, r, 1, 0, n - 1); }
};

// HLD
const int E = 0;
int anc[N], depth[N], head[N], heavy[N], pos[N], sz[N];
int cur_pos = 0;

int Op(int x, int y) { return max(x, y); }

void GetSize(int from) {
  heavy[from] = -1;
  sz[from] = 1;
  for (int to : adj[from]) {
    if (to == anc[from]) continue;
    depth[to] = depth[from] + 1;
    anc[to] = from;
    GetSize(to);
    sz[from] += sz[to];
    if (heavy[from] == -1 || sz[to] > sz[heavy[from]]) heavy[from] = to;
  }
}

void Build(int from, int top) {
  pos[from] = cur_pos++;
  head[from] = top;
  if (sz[from] > 1) {
    Build(heavy[from], top);
    for (int to : adj[from])
      if (to != anc[from] && to != heavy[from])
        Build(to, to);
  }
}

void BuildHLD(void){
  cur_pos = 0;
  anc[0] = -1;
  depth[0] = 0;
  GetSize(0);
  Build(0, 0);
}

Long Query(int u, int v, SegmentTree& st){
  Long ans = E;  // TODO: Define E, neutral element of Op
  while (head[u] != head[v]) {
    if (depth[head[u]] > depth[head[v]]) swap(u, v);
    ans = Op(ans, st.Query(pos[head[v]], pos[v]));  // TODO: Define Op
    v = anc[head[v]];
  }
  if (depth[u] > depth[v]) swap(u, v);
  ans = Op(ans, st.Query(pos[u], pos[v]));
  return ans;
}

void Update(int u, Long val, SegmentTree& st) {
  st.Update(pos[u], val);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    AddEdge(u, v);
  }
  BuildHLD();
  SegmentTree st(n);
  vector<int> euler(n);
  for (int i = 0; i < n; i++) euler[pos[i]] = a[i];
  st.Build(euler);
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int s, x;
      cin >> s >> x;
      s--;
      Update(s, x, st);
    } else {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      cout << Query(u, v, st) << " ";
    }
  }
  return 0;
}
