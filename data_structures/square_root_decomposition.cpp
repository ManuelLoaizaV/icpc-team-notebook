const int N = 2e5;
const int S = sqrt(N) + 1;
struct SquareRoot {
  Long a[N], ans[S], lazy[S];
  int n, s;
  SquareRoot(void) { n = s = 0; }
  int GetBlock(int i) { return i / s; }
  int GetLower(int i) { return (i / s) * s; }
  int GetUpper(int i) { return min(GetLower(i) + s - 1, n - 1); }
  void Clear(void) {
    for (int i = 0; i < n; i++) a[i] = ans[GetBlock(i)] = lazy[GetBlock(i)] = 0;
    n = s = 0;
  }
  void Build(const vector<Long>& v) {
    n = v.size();
    s = sqrt(n) + 1;
    for (int i = 0; i < n; i++) {
      a[i] = v[i];
      ans[GetBlock(i)] += v[i];
    }
  }
  void Update(int l, int r, Long x) {
    if (l > r) return;
    if (GetBlock(l) == GetBlock(r)) {
      int block = GetBlock(l);
      // Aplicar lazy
      for (int i = GetLower(l); i <= GetUpper(l); i++) a[i] += lazy[block];
      // Reiniciar lazy
      lazy[block] = 0;
      // Actualizar los valores individualmente
      for (int i = l; i <= r; i++) {
        a[i] += x;
        ans[block] += x;
      }
      return;
    }
    Update(l, GetUpper(l), x);
    Update(GetLower(r), r, x);
    int first = GetUpper(l) + 1;
    int last = GetLower(r) - 1;
    for (int i = first; i <= last; i += s) {
      // Aplicar actualizacion en bloques
      ans[GetBlock(i)] += x * (GetUpper(i) - GetLower(i) + 1);
      // Acumular lazy
      lazy[GetBlock(i)] += x;
    }
  }
  Long Query(int l, int r) {
    Long sum = 0;  // Elemento neutro de la operacion
    if (l > r) return sum;
    if (GetBlock(l) == GetBlock(r)) {
      int block = GetBlock(l);
      for (int i = l; i <= r; i++) sum += (a[i] + lazy[block]);
      return sum;
    }
    sum += Query(l, GetUpper(l));
    sum += Query(GetLower(r), r);
    int first = GetUpper(l) + 1;
    int last = GetLower(r) - 1;
    for (int i = first; i <= last; i += s) sum += ans[GetBlock(i)];
    return sum;
  }
} sq;
