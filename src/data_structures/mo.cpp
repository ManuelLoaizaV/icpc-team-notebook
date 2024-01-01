const int S = 800;
struct Query {
  int id, l, r;
  Query() {}
  Query(int id, int l, int r) : id(id), l(l), r(r) {}
  bool operator<(const Query& other) const {
    int block = l / S;
    int other_block = other.l / S;
    if (block != other_block) return (block < other_block);
    return (r > other.r);
  }
};
struct Mo {
  void Add(Long val, Long& ans) { ans += val; }
  void Delete(Long val, Long& ans) { ans -= val; }
  vector<Long> Build(const vector<Long>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<Long> ans(q.size());
    int l = 0;
    int r = -1;
    int acc = 0;
    for (int i = 0; i < q.size(); i++) {
      while (r < q[i].r) Add(a[++r], acc);
      while (l > q[i].l) Add(a[--l], acc);
      while (r > q[i].r) Delete(a[r--], acc);
      while (l < q[i].l) Delete(a[l++], acc);
      ans[q[i].id] = acc;
    }
    return ans;
  }
};