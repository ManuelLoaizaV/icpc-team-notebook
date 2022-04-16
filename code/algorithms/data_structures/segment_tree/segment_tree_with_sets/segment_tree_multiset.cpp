const int N = 3e4;
struct SegmentTree {
  int n;
  multiset<int> tree[4 * N];
  SegmentTree(void) {}
  SegmentTree(int new_n) { n = new_n; }
  int current[N];  // elementos en el estado actual
  int Merge(const int& x, const int& y) { return min(x, y); }
  multiset<int> Merge(const multiset<int>& left, const multiset<int>& right) {
    multiset<int> ans;
    for (auto x : left) ans.insert(x);
    for (auto x : right) ans.insert(x);
    return ans;
  }
  // O(n lg^2 n)
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id].insert(a[tl]);
      current[tl] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
      //tree[id] = tree[2 * id];
      //tree[id].insert(tree[2 * id + 1].begin(), tree[2 * id + 1].end());
    }
  }
  // O(lg^2(n))
  void Update(int pos, int x, int id, int tl, int tr) {
    tree[id].erase(tree[id].find(current[pos]));
    tree[id].insert(x);
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
  // Menor elemento >= k en a[l .. r]
  int Query(int l, int r, int k, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      auto it = tree[id].lower_bound(k);
      if (it == tree[id].end()) return INF;
      return *it;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, k, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, k, 2 * id + 1, tm + 1, tr);
    return Merge(Query(l, r, k, 2 * id, tl, tm), Query(l, r, k, 2 * id + 1, tm + 1, tr));
  }
  int Query(int l, int r, int k) { return Query(l, r, k, 1, 0, n - 1); }
} st;
