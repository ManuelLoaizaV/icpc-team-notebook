const int N = 1e5;
struct SegmentTree {
  bool marked[4 * N];
  Long lazy[4 * N];
  void Build(const vector<Long>& a, int id, int tl, int tr) {
    marked[id] = false;
    if (tl == tr) {
      lazy[id] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
    }
  }
  void Push(int id) {
    if (marked[id]) {
      // Asignar
      lazy[2 * id] = lazy[2 * id + 1] = lazy[id];
      marked[2 * id] = marked[2 * id + 1] = true;
      // Reiniciar
      marked[id] = false;
    }
  }
  void Update(int l, int r, Long val, int id, int tl, int tr) {
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      // Asignar
      lazy[id] = val;
      marked[id] = true;
    } else {
      Push(id);
      int tm = (tl + tr) / 2;
      Update(l, r, val, 2 * id, tl, tm);
      Update(l, r, val, 2 * id + 1, tm + 1, tr);
    }
  }
  Long Query(int pos, int id, int tl, int tr) {
    if (tl == tr) return lazy[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (pos <= tm) return Query(pos, 2 * id, tl, tm);
    return Query(pos, 2 * id + 1, tm + 1, tr);
  }
} st;
