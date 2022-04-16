#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5;
struct SegmentTree {
  int tree[4 * N];

  int Merge(int x) { return x; }

  int Merge(int x, int y) { return x + y; }

  // Complejidad en tiempo: O(n)
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {  // Estamos parados en una hoja del segment tree
      tree[id] = Merge(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }

  // Complejidad en tiempo: O(lg n)
  void Update(int pos, int val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = Merge(val);
    } else {
      int tm = (tl + tr) / 2;
      // Actualizamos alguno de nuestros nodos hijos
      if (pos <= tm) {
        Update(pos, val, 2 * id, tl, tm);
      } else {
        Update(pos, val, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }

  // Complejidad en tiempo: O(lg n)
  int Query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, 2 * id, tl, tm), Query(l, r, 2 * id + 1, tm + 1, tr));
  }
} st;

void Solve(int n) {
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  // Construyo el segment tree
  st.Build(a, 1, 0, n - 1);
  string s;
  while (cin >> s) {
    if (s[0] == 'E') break;
    if (s[0] == 'M') {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      cout << st.Query(l, r, 1, 0, n - 1) << '\n';
    } else {
      int x, r;
      cin >> x >> r;
      x--;
      st.Update(x, r, 1, 0, n - 1);
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t = 0;
  int n;
  while (cin >> n) {
    if (n == 0) break;
    t++;
    cout << "Case " << t << ":\n";
    Solve(n);
    cout << '\n';
  }
  return 0;
}
