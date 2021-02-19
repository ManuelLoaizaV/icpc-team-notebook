//https://www.spoj.com/problems/KQUERYO/
#include <bits/stdc++.h>
using namespace std;

const int N = 3e4;

struct SegmentTree {
  vector<int> tree[4 * N];
  vector<int> Merge(const vector<int>& left, const vector<int>& right) {
    int l = 0;
    int r = 0;
    int size = left.size() + right.size();
    vector<int> ans(size);
    for (int i = 0; i < size; i++) {
      if (l == left.size()) {
        ans[i] = right[r++];
      } else if (r == right.size()) {
        ans[i] = left[l++];
      } else if (left[l] < right[r]) {
        ans[i] = left[l++];
      } else {
        ans[i] = right[r++];
      }
    }
    return ans;
  }
  void Build(const vector<int>& a, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {a[tl]};
    } else {
      int tm = (tl + tr) / 2;
      Build(a, 2 * id, tl, tm);
      Build(a, 2 * id + 1, tm + 1, tr);
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  void Update(int pos, int x, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = {x};
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) {
        Update(pos, x, 2 * id, tl, tm);
      } else {
        Update(pos, x, 2 * id + 1, tm + 1, tr);
      }
      tree[id] = Merge(tree[2 * id], tree[2 * id + 1]);
    }
  }
  int Query(int l, int r, int k, int id, int tl, int tr) {
    if (l <= tl && tr <= r) {
      int pos = upper_bound(tree[id].begin(), tree[id].end(), k) - tree[id].begin();
      if (pos == tr - tl + 1) return 0;
      return tree[id].size() - pos;
    }
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, k, 2 * id, tl, tm);
    if (tm < l) return Query(l, r, k, 2 * id + 1, tm + 1, tr);
    return Query(l, r, k, 2 * id, tl, tm) + Query(l, r, k, 2 * id + 1, tm + 1, tr);
  }
} st;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, 1, 0, n - 1);
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
      last = st.Query(i - 1, j - 1, k, 1, 0, n - 1);
    }
    cout << last << '\n';
  }
  return 0;
}
