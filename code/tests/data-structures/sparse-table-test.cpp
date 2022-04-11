// https://www.spoj.com/problems/RMQSQ/en/
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

const int E = INT_MAX;
const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  int st[N][LG];
  int f(int x) { return x; }
  int f(int x, int y) { return min(x, y); }
  void Build(vector<int>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  int Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  st.Build(a, n);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << st.Query(l, r) << '\n';
  }
  return 0;
}