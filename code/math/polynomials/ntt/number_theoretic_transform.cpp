typedef long long Long;
typedef vector<Long> Polynomial;
const int N = 2e5;
const Long MOD = 998244353;
const Long ROOT = 3;
const Long ROOT_INV = 332748118;
struct Field {
  Long n;
  Field(Long _n = 0) : n(_n) {}
  Field operator + (const Field& o) const { return (n + o.n) % MOD; }
  Field operator - (const Field& o) const { return (n - o.n + MOD) % MOD; }
  Field operator * (const Field& o) const { return (n * o.n) % MOD; }
  Field operator *= (const Field& o) {
    n *= o.n;
    n %= MOD;
    return *this;
  }
};
const Field TWO_INV(499122177);
Long Mul(Long a, Long b) { return (a * b) % MOD; }
Long FastPow(Long a, Long b) {
  Long ans = 1;
  while (b > 0) {
    if (b & 1) ans = Mul(ans, a);
    a = Mul(a, a);
    b >>= 1;
  }
  return ans;
}
void NTT(vector<Field>& a, bool is_inverse, Field w_n) {
  int n = a.size();
  if (n == 1) return;
  Field w(1);
  vector<Field> a_0(n / 2), a_1(n / 2);
  for (int i = 0; 2 * i < n; i++) {
    a_0[i] = a[2 * i];
    a_1[i] = a[2 * i + 1];
  }
  NTT(a_0, is_inverse, w_n * w_n);
  NTT(a_1, is_inverse, w_n * w_n);
  for (int i = 0; 2 * i < n; i++) {
    a[i] = a_0[i] + w * a_1[i];
    a[i + n / 2] = a_0[i] - w * a_1[i];
    if (is_inverse) {
      a[i] *= TWO_INV;
      a[i + n / 2] *= TWO_INV;
    }
    w *= w_n;
  }
}
Polynomial operator * (const Polynomial& a, const Polynomial& b) {
  int n = 1;
  vector<Field> dft_a(a.begin(), a.end());
  vector<Field> dft_b(b.begin(), b.end());
  while (n < a.size() + b.size()) n <<= 1;
  dft_a.resize(n);
  dft_b.resize(n);
  Field w_n(FastPow(ROOT, (MOD - 1) / n));
  // Evaluation in O(n lg(n))
  NTT(dft_a, false, w_n);
  NTT(dft_b, false, w_n);
  // Pointwise multiplication in O(n)
  vector<Field> dft_c(n);
  for (int i = 0; i < n; i++) dft_c[i] = dft_a[i] * dft_b[i];
  w_n = Field(FastPow(ROOT_INV, (MOD - 1) / n));
  // Interpolation in O(n lg(n))
  NTT(dft_c, true, w_n);
  Polynomial c(a.size() + b.size() - 1);
  for (int i = 0; i < c.size(); i++) c[i] = dft_c[i].n;
  return c;
}
