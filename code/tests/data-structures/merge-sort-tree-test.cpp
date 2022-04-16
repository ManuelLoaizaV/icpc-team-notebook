// https://www.spoj.com/problems/KQUERYO/
#include <bits/stdc++.h>
using namespace std;

const int N = 3e4;

struct MergeSortTree {
  vector<int> tree[4 * N];
  int n;
  MergeSortTree(int n) : n(n) {}
  vector<int> Merge(const vector<int>& left, const vector<int>& right) {
    int l = 0;
    int r = 0;
    vector<int> ans;
    int size = left.size() + right.size();
    for (int i = 0; i < size; i++) {
      if (l == left.size()) {
        ans.push_back(right[r++]);
      } else if (r == right.size()) {
        ans.push_back(left[l++]);
      } else if (left[l] < right[r]) {
        ans.push_back(left[l++]);
      } else {
        ans.push_back(right[r++]);
      }
    }
    return ans;
  }
  // O(n lgn)
  void Build(int id, int tl, int tr, const vector<int>& v) {
    if (tl == tr) {
      tree[id] = {v[tl]};
    } else {
      int tm = (tl + tr) / 2;
      Build(2 * id, tl, tm, v);
      Build(2 * id + 1, tm + 1, tr, v);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  // O(n). Utilizar multiset u ost de nodos para O(lg^2 n).
  void Update(int pos, int val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {val};
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, val, 2 * id, tl, tm);
      } else {
        Update(pos, val, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  // O(lg^2(n))
  int Query(int l, int r, int x, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      auto it = upper_bound(tree[id].begin(), tree[id].end(), x);
      if (it == tree[id].end()) return 0;
      int pos = it - tree[id].begin();
      return tree[id].size() - pos;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, x, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, x, 2 * id + 1, tm + 1, tr);
    return Query(l, r, x, 2 * id, tl, tm) + Query(l, r, x, 2 * id + 1, tm + 1, tr);
  }
  void Build(const vector<int>& v) { Build(1, 0, n - 1, v); }
  void Update(int pos, int val) { Update(pos, val, 1, 0, n - 1); }
  int Query(int l, int r, int x) { return Query(l, r, x, 1, 0, n - 1); }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  MergeSortTree mt(n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  mt.Build(a);
  int q;
  cin >> q;
  int last = 0;
  while (q--) {
    int a, b, c;
    cin >> a >> b >> c;
    int i = max(1, a ^ last);
    int j = min(n, b ^ last);
    int k = c ^ last;
    if (i > j) {
      last = 0;
    } else {
      last = mt.Query(i - 1, j - 1, k);
    }
    cout << last << '\n';
  }
  return 0;
}
