//https://codeforces.com/problemset/problem/292/E
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

struct SegmentTree {
  bool marked[4 * N];
  int lazy[4 * N];
  void Build(int id, int tl, int tr) {
    marked[id] = false;
    if (tl == tr) {
      lazy[id] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm);
      Build(2 * id + 1, tm + 1, tr);
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
  void Update(int l, int r, int val, int id, int tl, int tr) {
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
  int Query(int pos, int id, int tl, int tr) {
    if (tl == tr) return lazy[id];
    int tm = (tl + tr) / 2;
    Push(id);
    if (pos <= tm) return Query(pos, 2 * id, tl, tm);
    return Query(pos, 2 * id + 1, tm + 1, tr);
  }
} st;

struct Consulta {
  int x, y, k;
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  st.Build(1, 0, n - 1);
  vector<Consulta> q;
  while (m--) {
    int t;
    cin >> t;
    if (t == 1) {
      int x, y, k;
      cin >> x >> y >> k;
      x--;
      y--;
      st.Update(y, y + k - 1, q.size(), 1, 0, n - 1);
      q.push_back({x, y, k});
    } else {
      int pos;
      cin >> pos;
      pos--;
      int id = st.Query(pos, 1, 0, n - 1);
      if (id == -1) {
        cout << b[pos] << '\n';
      } else {
        cout << a[q[id].x + (pos - q[id].y)] << '\n';
      }
    }
  }
  return 0;
}
