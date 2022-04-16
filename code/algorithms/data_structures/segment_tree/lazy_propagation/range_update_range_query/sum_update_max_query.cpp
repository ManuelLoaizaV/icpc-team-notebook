const int N = 1e5;
struct SegmentTree {
  Long tree[4 * N], lazy[4 * N];
  Long Merge(const Long& x, const Long& y) { return max(x, y); }
  void Build(const vector<int>& a, int id, int tl, int tr) {
    // Reiniciar
    lazy[id] = 0;
    if (tl == tr) {
      tree[id] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Push(int id) {
    if (lazy[id] == 0) return;
    // Aplicar
    tree[2 * id] += lazy[id];
    tree[2 * id + 1] += lazy[id];
    // Acumular
    lazy[2 * id] += lazy[id];
    lazy[2 * id + 1] += lazy[id];
    // Reiniciar
    lazy[id] = 0;
  }
  void Update(int l, int r, Long delta, int id, int tl, int tr) {
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      // Aplicar
      tree[id] += delta;
      // Acumular
      lazy[id] += delta;
    } else {
      int tm = (tl + tr) / 2;
      Push(id);
      Update(l, r, delta, 2 * id, tl, tm);
      Update(l, r, delta, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  Long Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;
