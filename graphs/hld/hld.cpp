int anc[N], depth[N], head[N], heavy[N], pos[N], sz[N];
int cur_pos = 0;
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
void Initialize(void){
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
