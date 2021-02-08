const int N = 1e5;
struct SegmentTree {
  Long tree[4 * N];
  Long Merge(const Long& x) { return x; }
  Long Merge(const Long& x, const Long& y) { return x + y; }
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
} st;
