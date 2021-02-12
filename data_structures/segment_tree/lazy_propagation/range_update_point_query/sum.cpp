const int N = 1e5;
struct SegmentTree {
  int lazy[4 * N];
  void Build(const vector<int>& a, int id, int tl, int tr) {
    lazy[id] = 0;
    if (tl == tr) {
      lazy[id] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
    }
  }
  void Push(int id) {
    if (lazy[id] == 0) return;
    // Acumular
    lazy[2 * id] += lazy[id];
    lazy[2 * id + 1] += lazy[id];
    // Reiniciar
    lazy[id] = 0;
  }
  void Update(int l, int r, int delta, int id, int tl, int tr) {
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      // Acumular
      lazy[id] += delta;
    } else {
      Push(id);
      int tm = (tl + tr) / 2;
      Update(l, r, delta, 2 * id, tl, tm);
      Update(l, r, delta, 2 * id + 1, tm + 1, tr);
    }
  }
  int Query(int pos, int id, int tl, int tr) {
    if (tl == tr) return lazy[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (pos <= tm) return Query(pos, 2 * id, tl, tm);
    return Query(pos, 2 * id + 1, tm + 1, tr);
  }
} st;
