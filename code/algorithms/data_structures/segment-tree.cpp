const int N = 1e5;
struct SegmentTree {
  Long tree[4 * N];
  int n;
  SegmentTree(int n) : n(n) {}
  Long Merge(const Long& x) { return x; }
  Long Merge(const Long& x, const Long& y) { return x + y; }
  void Build(int id, int tl, int tr, const vector<Long>& v) {
    if (tl == tr) {
      tree[id] = Merge(v[tl]);
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm, v);
      Build(2 * id + 1, tm + 1, tr, v);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
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
  Long Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
  void Build(const vector<int>& v) { Build(1, 0, n - 1, v); }
  void Update(int pos, int val) { Update(pos, val, 1, 0, n - 1); }
  Long Query(int l, int r) { return Query(l, r, 1, 0, n - 1); }
};
