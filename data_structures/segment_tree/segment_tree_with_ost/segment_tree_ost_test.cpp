//https://www.spoj.com/problems/KQUERY2/en/
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int, int> Pair;
typedef tree<Pair, null_type, less<Pair>, rb_tree_tag, tree_order_statistics_node_update> OST;
// find_by_order(k): Returns an iterator to the k-th largest element (0 indexed).
// order_of_key(k): Returns the number of items that are stricly smaller than k.

const int INF = 1e9;
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


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  scanf("%d", &n);
  SegmentTree st(n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  st.Build(a, 1, 0, n - 1);
  int q;
  scanf("%d", &q);
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, v;
      scanf("%d %d", &i, &v);
      i--;
      st.Update(i, v);
    } else {
      int i, j, k;
      scanf("%d %d %d", &i, &j, &k);
      printf("%d\n", st.Query(i - 1, j - 1, {k + 1, -INF}));
    }
  }
  return 0;
}
