#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef pair<int, int> Pair;
typedef tree<Pair, null_type, less<Pair>, rb_tree_tag, tree_order_statistics_node_update> OST;
const int INF;
const int N = 3e4;
struct SegmentTree {
  int n;
  OST tree[4 * N];
  SegmentTree(void) {}
  SegmentTree(int new_n) { n = new_n; }
  int current[N];  // elementos en el estado actual
  int Merge(const int& x, const int& y) { return x + y; }
  // O(n lg^2 n)
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id].insert({a[tl], tl});
      current[tl] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = tree[2 * id];
      for (auto x : tree[2 * id + 1]) tree[id].insert(x);
    }
  }
  // O(lg^2(n))
  void Update(int pos, int x, int id, int tl, int tr) {
    tree[id].erase({current[pos], pos});
    tree[id].insert({x, pos});
    if (tl == tr) {
      current[pos] = x;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, x, 2 * id, tl, tm);
      } else {
        Update(pos, x, 2 * id + 1, tm + 1, tr);
      }
    }
  }
  void Update(int pos, int x) { Update(pos, x, 1, 0, n - 1); }
  int Query(int l, int r, const Pair& k, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id].size() - tree[id].order_of_key(k);
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, k, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, k, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, k, 2 * id, tl, tm), Query(l, r, k, 2 * id + 1, tm + 1, tr));
  }
  int Query(int l, int r, const Pair& k) { return Query(l, r, k, 1, 0, n - 1); }
};
