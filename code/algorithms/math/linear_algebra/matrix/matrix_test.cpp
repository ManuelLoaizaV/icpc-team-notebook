#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;
typedef vector<vector<Long>> Matrix;

const Long MOD = 1e9 + 7;

Long Add(Long a, Long b) {
  return (a + b) % (MOD - 1);
}

Long Sub(Long a, Long b) {
  return (a - b + (MOD - 1)) % (MOD - 1);
}

Long Mul(Long a, Long b) {
  if (a * b < 0) return Sub(0, abs(a * b) % (MOD - 1));
  return (a * b) % (MOD - 1);
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

Matrix FastPow(Matrix a, Long b) {
  assert(a.size() == a[0].size());
  Matrix ans = GetMatrix(a.size(), a.size(), true);
  while (b > 0) {
    if (b & 1) ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}

Long FastPow(Long a, Long b) {
  Long ans = 1LL;
  while (b > 0) {
    if (b & 1) ans = (ans * a) % MOD;
    a = (a * a) % MOD;
    b >>= 1;
  }
  return ans;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, c;
  cin >> n;
  Long f[3];
  for (int i = 0; i < 3; i++) cin >> f[i];
  cin >> c;
  if (n < 4) {
    cout << f[n - 1] << '\n';
    return 0;
  }
  Matrix factor = GetMatrix(3, 3, false);
  factor[0][0] = factor[0][1] = factor[0][2] = factor[1][0] = factor[2][1] = 1LL;
  factor = FastPow(factor, n - 3);

  Matrix base = GetMatrix(3, 1, false);
  base[0][0] = 1;
  Matrix exp_f3 = factor * base;
  base[0][0] = 0;
  base[1][0] = 1;
  Matrix exp_f2 = factor * base;
  base[1][0] = 0;
  base[2][0] = 1;
  Matrix exp_f1 = factor * base;
  base = GetMatrix(5, 1, 0);
  base[3][0] = 3;
  base[4][0] = 1;

  Matrix cnt = GetMatrix(5, 5, false);
  cnt[0][0] = cnt[0][1] = cnt[0][2] = cnt[1][0] = cnt[2][1] = cnt[3][3] = cnt[3][4] = cnt[4][4] = 1LL;
  cnt[0][3] = 2LL;
  cnt[0][4] = -4LL;
  cnt = FastPow(cnt, n - 3);
  Matrix exp_c = cnt * base;

  Long f3 = FastPow(f[2], exp_f3[0][0]);
  Long f2 = FastPow(f[1], exp_f2[0][0]);
  Long f1 = FastPow(f[0], exp_f1[0][0]);
  Long fc = FastPow(c, exp_c[0][0]);
  Long ans = (fc * f3) % MOD;
  ans = (ans * f2) % MOD;
  ans = (ans * f1) % MOD;
  cout << ans << '\n';
  return 0;
}
