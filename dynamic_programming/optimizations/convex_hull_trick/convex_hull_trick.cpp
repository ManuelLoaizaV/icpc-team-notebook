struct Line {
  mutable Long m, b, p;
  bool operator < (const Line& other) const { return m < other.m; }
  bool operator < (Long x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
  //static const Double INF = 1/.0;
  static const Long INF = LLONG_MAX;
  //Double Div(Double a, Double b) { return a / b; }
  Long Div(Long a, Long b) { return a / b - ((a ^ b) < 0 && a % b); }
  bool Intersect(iterator x, iterator y) {
    if (y == end()) return x->p = INF, 0;
    if (x->m == y->m) {
      x->p = x->b > y->b ? INF : -INF;
    } else {
      x->p = Div(y->b - x->b, x->m - y->m);
    }
    return x->p >= y->p;
  }
  // Agregar recta de la forma mx + b
  void Add(Long m, Long b) {
    auto z = insert({m, b, 0});
    auto y = z++;
    auto x = y;
    while (Intersect(y, z)) z = erase(z);
    if (x != begin() && Intersect(--x, y)) Intersect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) Intersect(x, erase(y));
  }
  // Obtener maximo valor en el punto x
  Long Query(Long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
};
