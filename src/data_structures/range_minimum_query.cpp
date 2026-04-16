// Range minimum/maximum query using a sparse table.
// Set the comparison policy to std::greater<T> for maximum queries.
template <typename T, class Comparison = std::less<T>> struct RMQ {
  int N;
  vector<T> values;
  vector<vector<int>> sparse_table;
  Comparison compare;
  RMQ(const vector<T> &_values = {}) {
    compare = Comparison();
    if (!_values.empty())
      Compute(_values);
  }

  // Computes the sparse table.
  // Time complexity: O(N lg N).
  void Compute(const vector<T> &_values) {
    N = (int)_values.size();
    values = _values;
    int levels = HighestBit(N) + 1;
    sparse_table.resize(levels);
    for (int level = 0; level < levels; level++)
      sparse_table[level].resize(N - (1 << level) + 1);
    for (int i = 0; i < N; i++)
      sparse_table[0][i] = i;
    for (int level = 1; level < levels; level++)
      for (int i = 0; i <= N - (1 << level); i++)
        sparse_table[level][i] =
            BetterIndex(sparse_table[level - 1][i],
                        sparse_table[level - 1][i + (1 << (level - 1))]);
  }

  // Returns floor(lg n) which is the index of the highest set bit or -1 if n is
  // zero. Since C++20, we can use std::bit_width from <bit> header. Fallback
  // for older compilers: 31 - __builtin_clz(n).
  static int HighestBit(unsigned n) {
    if (n == 0)
      return -1;
    return std::bit_width(n) - 1;
  }

  // Compares two indices and returns the one pointing to the better value.
  // In case of a tie, the rightmost index is returned.
  int BetterIndex(int L, int R) const {
    return compare(values[L], values[R]) ? L : R;
  }

  // Returns the index of the maximum/minimum value in the range [L, R).
  int QueryIndex(int L, int R) const {
    assert(0 <= L && L < R && R <= N);
    int level = HighestBit(R - L);
    return BetterIndex(sparse_table[level][L],
                       sparse_table[level][R - (1 << level)]);
  }

  // Returns the minimum/maximum value in the range [L, R).
  // Time complexity: O(1).
  T QueryValue(int L, int R) const { return values[QueryIndex(L, R)]; }
};