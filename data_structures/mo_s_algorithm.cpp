const int SZ = 800;
struct Query {
  int id, l, r;
  Query() {}
  Query(int id, int l, int r) : id(id), l(l), r(r) {}
  bool operator < (const Query& other) const {
    int block = l / SZ;
    int other_block = other.l / SZ;
    if (block != other_block) return (block < other_block);
    return (r > other.r);
  }
};
struct Mo {
  void Add(int val, int& ans) { ans += val; }
  void Delete(int val, int& ans) { ans -= val; }
  vector<int> Build(const vector<int>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<int> ans(q.size());
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
