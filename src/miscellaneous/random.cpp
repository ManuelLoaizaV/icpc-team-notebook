namespace Random {
  int64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
  std::mt19937_64 gen(seed);
  Long Get(Long l, Long r) { return std::uniform_int_distribution<Long>(l, r)(gen); }
  std::vector<Long> Permutation(size_t n) {
    std::vector<Long> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::shuffle(p.begin(), p.end(), gen);
    return p;
  }
}