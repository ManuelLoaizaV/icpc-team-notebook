#include <bits/stdc++.h>
using namespace std;

const int SZ = 800;
struct Query {
  int id, l, r;
  Query() {}
  Query(int id, int l, int r) : id(id), l(l), r(r) {}
  bool operator<(const Query& other) const {
    int block = l / SZ;
    int other_block = other.l / SZ;
    if (block != other_block) return (block < other_block);
    return (r > other.r);
  }
};

struct Mo {
  void Add(int val, int& ans) { ans += val; }
  void Delete(int val, int& ans) { ans -= val; }
  vector<int> Build(const vector<int>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<int> ans(q.size());
    int l = 0;
    int r = -1;
    int acc = 0;
    for (int i = 0; i < q.size(); i++) {
      while (r < q[i].r) Add(a[++r], acc);
      while (l > q[i].l) Add(a[--l], acc);
      while (r > q[i].r) Delete(a[r--], acc);
      while (l < q[i].l) Delete(a[l++], acc);
      ans[q[i].id] = acc;
    }
    return ans;
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int q;
  cin >> q;
  vector<Query> queries(q);
  for (int i = 0; i < q; i++) {
    cin >> queries[i].l >> queries[i].r;
    queries[i].id = i;
  }

  Mo mo;
  vector<int> ans = mo.Build(a, queries);
  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
  cout << '\n';
  return 0;
}
