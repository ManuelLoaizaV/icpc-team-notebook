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