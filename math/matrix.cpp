typedef long long Long;
typedef vector<vector<Long>> Matrix;
const Long MOD = 1e9 + 7;
Long Add(Long a, Long b) {
  return (a + b) % MOD;
}
Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}
Long Mul(Long a, Long b) {
  if (a * b < 0) return Sub(0, abs(a * b) % MOD);
  return (a * b) % MOD;
}
Matrix GetMatrix(int n, int m, bool is_identity) {
  Matrix matrix = Matrix(n, vector<Long> (m, 0));
  if (is_identity) {
    assert(n == m);
    for (int i = 0; i < n; i++) matrix[i][i] = 1LL;
  }
  return matrix;
}
Matrix operator + (const Matrix& a, const Matrix& b) {
  Long n = a.size();
  Long m = a[0].size();
  assert(a.size() == b.size());
  assert(a[0].size() == b[0].size());
  Matrix c = GetMatrix(n, m, false);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      c[i][j] = Add(a[i][j], b[i][j]);
  return c;
}
Matrix operator * (const Matrix& a, const Matrix& b) {
  assert(a[0].size() == b.size());
  int n = a.size();
  int m = a[0].size();
  int p = b[0].size();
  Matrix c = GetMatrix(n, p, false);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      for (int k = 0; k < m; k++)
        c[i][j] = Add(c[i][j], Mul(a[i][k], b[k][j]));
  return c;
}
Matrix FastPow(const Matrix& a, Long b) {
  assert(a.size() == a[0].size());
  Matrix ans = GetMatrix(a.size(), a.size(), true);
  while (b > 0) {
    if (b & 1) ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}
