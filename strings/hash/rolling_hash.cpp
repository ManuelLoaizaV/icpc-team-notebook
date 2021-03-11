const int N = 1e5;
const int M = 2;
const Long MOD = 1e9 + 7;
const Long C = (Long) 'a';
const Long B[M] = {29LL, 31LL};
Long P[N][M];
Long Add(Long a, Long b) { return (a + b) % MOD; }
Long Mul(Long a, Long b) { return (a * b) % MOD; }
Long Sub(Long a, Long b) { return (a - b + MOD) % MOD; }
struct Hash {
  Long h[N][M];  // h[i][j] = s[0] * B[j] ^ i + ... + s[i - 1] * B[j] + s[i]
  void Build(const string& s) {
    int n = s.size();
    for (int j = 0; j < M; j++) h[0][j] = s[0] - C + 1;
    for (int i = 1; i < n; i++)
      for (int j = 0; j < M; j++)
        h[i][j] = Add(Mul(h[i - 1][j], B[j]), s[i] - C + 1);
  }
  vector<Long> Query(int l, int r) {
    vector<Long> ans(M);
    for (int j = 0; j < M; j++) {
      if (l == 0) {
        ans[j] = h[r][j];
      } else {
        ans[j] = Sub(h[r][j], Mul(h[l - 1][j], P[r - l + 1][j]));
      }
    }
    return ans;
  }
};
void Precalculate(int n) {
  for (int j = 0; j < M; j++) P[0][j] = 1;
  for (int i = 1; i < n; i++)
    for (int j = 0; j < M; j++)
      P[i][j] = Mul(P[i - 1][j], B[j]);
}
