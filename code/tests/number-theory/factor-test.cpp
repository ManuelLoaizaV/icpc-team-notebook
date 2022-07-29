// https://codeforces.com/gym/102966/problem/L
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e7;
int primes[N + 1];
void Sieve(void) {
  for (int i = 0; i <= N; i++) primes[i] = i;
  for (int i = 2; i <= N; i++) {
    if (primes[i] != i) continue;
    for (Long j = 1LL * i * i; j <= N; j += i) primes[j] = i;
  }
}

vector<pair<int, int>> Factor(int n) {
  vector<pair<int, int>> factors;
  while (n > 1) {
    int p = primes[n];
    int e = 0;
    while (n % p == 0) {
      n /= p;
      e++;
    }
    factors.push_back({p, e});
  }
  sort(factors.begin(), factors.end());
  return factors;
}

void Solve(void) {
  set<int> primes;
  for (int i = 0; i < 2; i++) {
    int n;
    cin >> n;
    vector<pair<int, int>> factors = Factor(n);
    for (pair<int, int> factor : factors) {
      primes.insert(factor.first);
    }
  }
  cout << primes.size() << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve();
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}