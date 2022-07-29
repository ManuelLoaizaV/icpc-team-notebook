#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e7;
Long primes[N + 1];
void Sieve(void) {
  for (int i = 0; i <= N; i++) primes[i] = i;
  for (Long i = 2; i <= N; i++) {
    if (primes[i] != i) continue;
    for (Long j = 1LL * i * i; j <= N; j += i) primes[j] = min(primes[j], i);
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve();
  int n, k;
  cin >> n >> k;
  int cnt = 0;
  int cur = 2;
  while (true) {
    if (primes[cur] != cur && primes[cur] > n) cnt++;
    if (cnt == k) break;
    cur++;
  }
  cout << cur << '\n';
  return 0;
}