const int N = 1e5;
struct FenwickTree {
  int tree[N + 1];
  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }
  int Query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= (i & -i);
    }
    return sum;
  }
} ft;
