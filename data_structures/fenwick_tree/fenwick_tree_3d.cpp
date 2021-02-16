const int N = 128;
struct FenwickTree {
  Long tree[N + 1][N + 1][N + 1];
  void Update(int i, int j, int k, Long delta) {
    while (i <= N) {
      int y = j;
      while (y <= N) {
        int z = k;
        while (z <= N) {
          tree[i][y][z] += delta;
          z += (z & -z);
        }
        y += (y & -y);
      }
      i += (i & -i);
    }
  }
  Long Query(int i, int j, int k) {
    Long ans = 0;
    while (i > 0) {
      int y = j;
      while (y > 0) {
        int z = k;
        while (z > 0) {
          ans += tree[i][y][z];
          z -= (z & -z);
        }
        y -= (y & -y);
      }
      i -= (i & -i);
    }
    return ans;
  }
  Long Query(int x1, int y1, int z1, int x2, int y2, int z2) {
    return Query(x2, y2, z2)
      - Query(x1 - 1, y2, z2) - Query(x2, y1 - 1, z2) - Query(x2, y2, z1 - 1)
      + Query(x1 - 1, y1 - 1, z2) + Query(x1 - 1, y2, z1 - 1)
      + Query(x2, y1 - 1, z1 - 1) - Query(x1 - 1, y1 - 1, z1 - 1);
  }
} ft;
