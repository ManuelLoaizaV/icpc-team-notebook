const int N = 1e7;
int primes[N + 1];
void Sieve(void) {
  for (int i = 0; i <= N; i++) primes[i] = i;
  for (int i = 2; i <= N; i++) {
    if (primes[i] != i) continue;
    for (Long j = 1LL * i * i; j <= N; j += i) primes[j] = i;
  }
}