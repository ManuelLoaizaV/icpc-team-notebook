// https://www.spoj.com/problems/MATSUM/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1025;
struct FenwickTree {
  Long tree[N + 1][N + 1];
  void Clear(int n, int m) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        tree[i][j] = 0;
      }
    }
  }
  void Update(int i, int y, Long delta) {
    while (i <= N) {
      int j = y;
      while (j <= N) {
        tree[i][j] += delta;
        j += (j & -j);
      }
      i += (i & -i);
    }
  }
  Long Query(int i, int y) {
    Long ans = 0;
    while (i > 0) {
      int j = y;
      while (j > 0) {
        ans += tree[i][j];
        j -= (j & -j);
      }
      i -= (i & -i);
    }
    return ans;
  }
  void Update(int x1, int y1, int x2, int y2, Long delta) {
    Update(x1, y1, delta);
    Update(x2 + 1, y1, -delta);
    Update(x1, y2 + 1, -delta);
    Update(x2 + 1, y2 + 1, delta);
  }
  Long Query(int x1, int y1, int x2, int y2) {
    return Query(x2, y2) - Query(x2, y1 - 1) - Query(x1 - 1, y2) + Query(x1 - 1, y1 - 1);
  }
} ft;

void Solve(void) {
  Long n;
  cin >> n;
  string s;
  ft.Clear(n, n);
  while (true) {
    cin >> s;
    if (s[0] == 'E') break;
    if (s[1] == 'E') {
      int x, y;
      Long num;
      cin >> x >> y >> num;
      Long delta = num - ft.Query(x + 1, y + 1, x + 1, y + 1);
      ft.Update(x + 1, y + 1, delta);
    } else {
      int i, j, x, y;
      cin >> i >> j >> x >> y;
      cout << ft.Query(i + 1, j + 1, x + 1, y + 1) << '\n';
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
