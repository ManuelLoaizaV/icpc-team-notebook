const int N = 1025;
template<typename T>
struct FenwickTree {
  T tree[N + 1][N + 1];
  void Init(int n, int m) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        tree[i][j] = T();
      }
    }
  }
  void Update(int i, int y, T change) {
    while (i <= N) {
      int j = y;
      while (j <= N) {
        tree[i][j] += change;
        j += (j & -j);
      }
      i += (i & -i);
    }
  }
  T Query(int i, int y) {
    T ans = 0;
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
  void Update(int x1, int y1, int x2, int y2, T change) {
    Update(x1, y1, change);
    Update(x2 + 1, y1, -change);
    Update(x1, y2 + 1, -change);
    Update(x2 + 1, y2 + 1, change);
  }
  T Query(int x1, int y1, int x2, int y2) {
    return Query(x2, y2) - Query(x2, y1 - 1) - Query(x1 - 1, y2) + Query(x1 - 1, y1 - 1);
  }
};
