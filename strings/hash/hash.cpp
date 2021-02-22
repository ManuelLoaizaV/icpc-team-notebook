const int N = 1e5;
const Long B[2] = {29LL, 31LL};
const Long MOD = 1e9 + 7;
Long P[N][2];
struct Hash {
  Long h[N][2];
  void Initialize(const string& s) {
    int n = s.size();
    h[0][0] = h[0][1] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        h[i][j] = Add(Mul(h[i - 1][j], B[j]), s[i] - 'a' + 1);
      }
    }
  }
  Pair Query(int l, int r) {
    vector<Long> ans(2);
    for (int j = 0; j < 2; j++) {
      if (l == 0) {
        ans[j] = h[r][j];
      } else {
        ans[j] = Sub(h[r][j], Mul(h[l - 1][j], P[r - l + 1][j]));
      }
    }
    return {ans[0], ans[1]};
  }
};
void Precalculate(int n) {
  P[0][0] = P[0][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      P[i][j] = Mul(P[i - 1][j], B[j]);
    }
  }
}
