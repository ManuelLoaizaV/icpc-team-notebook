vector<Long> f, primes;
vector<bool> is_prime;
void Sieve(int n) {
  is_prime = vector<bool>(n + 1, true);
  f = vector<Long> f(n, 1);
  f[1] = 1;
  for (Long i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      f[i] = i - 1;  // TODO
    }
    for (Long j = 0; j < (int) primes.size() && i * primes[j] <= n; j++) {
      is_prime[i * primes[j]] = false;
      if (i % primes[j] == 0) {
        f[i * primes[j]] = f[i] * prime[j];  // TODO
        break;
      } else {
        f[i * primes[j]] = f[i] * f[primes[j]];  // TODO
      }
    }
  }
}
