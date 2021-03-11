//https://www.spoj.com/problems/NHAY/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 2e6;
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

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Precalculate(N);
  int n, m;
  string p, t;
  Hash hp, ht;
  while (cin >> n) {
    cin >> p >> t;
    m = (int) t.size();
    hp.Build(p);
    ht.Build(t);
    for (int i = 0; i < m - n + 1; i++) {
      if (hp.Query(0, n - 1) == ht.Query(i, i + n - 1)) {
        cout << i << '\n';
      }
    }
    cout << '\n';
  }
  return 0;
}
