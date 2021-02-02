//https://cses.fi/problemset/task/1648/
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 2e5;
const int S = sqrt(N) + 1;

struct SquareRoot {
  Long a[N], ans[S], lazy[S];
  int n, sq;
  int GetBlock(int i) { return i / sq; }
  int GetLower(int i) { return (i / sq) * sq; }
  int GetUpper(int i) { return min(GetLower(i) + sq - 1, n - 1); }
  void Clear(void) {
    for (int i = 0; i < n; i++) a[i] = ans[GetBlock(i)] = lazy[GetBlock(i)] = 0;
    n = sq = 0;
  }
  void Build(const vector<Long>& v) {
    n = v.size();
    sq = sqrt(n) + 1;
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
    for (int i = first; i <= last; i += sq) {
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
    for (int i = first; i <= last; i += sq) sum += ans[GetBlock(i)];
    return sum;
  }
} sq;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sq.Build(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int k;
      Long u;
      cin >> k >> u;
      k--;
      sq.Update(k, k, u - sq.Query(k, k));
    } else {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      cout << sq.Query(l, r) << '\n';
    }
  }
  return 0;
}
