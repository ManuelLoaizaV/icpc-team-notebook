const int E = INT_MAX;
const int N = 1e5;
const int LG = 32 - __builtin_clz(N);
struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return min(x, y); }
  void Build(const vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(lg n). Modificar el elemento neutro E dependiendo de la operacion.
  int Query(int l, int r) {
    int ans = E;
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    for (int j = lg; j >= 0; j--) {
      if ((1 << j) <= range) {
        ans = f(ans, st[l][j]);
        l += (1 << j);
        range -= (1 << j);
      }
    }
    return ans;
  }
  // O(lg n). No se necesita definir un elemento neutro para la operacion.
  int Query(int l, int r) {
    int ans = st[l][0];
    if (l == r) return ans;
    l++;
    int range = r - l + 1;
    while (range > 0) {
      int step = range & -range;
      int lg = __builtin_ctz(step);
      ans = f(ans, st[l][lg]);
      l += step;
      range -= step;
    }
    return ans;
  }
  // O(1). Solo funciona con operadores idempotentes.
  int Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;
