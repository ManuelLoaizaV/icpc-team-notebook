mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long GetRandom(Long l, Long r) {
  return uniform_int_distribution<Long>(l, r)(rng);
}
vector<Long> GetPermutation(int n) {
  vector<Long> permutation(n);
  for (int i = 0; i < n; i++) permutation[i] = i;
  shuffle(permutation.begin(), permutation.end(), rng);
  return permutation;
}