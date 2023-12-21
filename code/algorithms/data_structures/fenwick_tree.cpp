// Fenwick Tree structure works as an OST/multiset for indexes within the range [0, tree_n).
// Set(index, 1): set.insert(index).
// Update(index, 1): multiset.insert(index).
// Set(index, 0): set.erase(index).
// Update(index, -1): multiset.erase(index).
// Get(index): set.count(index), multiset.count(index).
// Query(index): ost.order_of_key(index).
// FindLastPrefix(k): Find k-th smallest element (0-indexed). Returns tree_n for k >= multiset.size().
template<typename T>
struct FenwickTree {
  int tree_n = 0;
  T tree_sum = T();
  vector<T> tree;
  FenwickTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    tree_n = n;
    tree.assign(tree_n + 1, T());
  }
  // Initialization in O(n)
  template<typename A>
  void Build(const A& initial) {
    assert(int(initial.size()) == tree_n);
    tree_sum = T();
    for (int i = 1; i <= tree_n; i++) {
      tree[i] = initial[i - 1];
      tree_sum += initial[i - 1];
      for (int k = (i & -i) >> 1; k > 0; k >>= 1)
        tree[i] += tree[i - k];
    }
  }
  // Adds change to a[index]
  void Update(int index, const T& change) {
    assert(0 <= index && index < tree_n);
    tree_sum += change;
    for (int i = index + 1; i <= tree_n; i += (i & -i))
      tree[i] += change;
  }
  // Returns the sum of the range [0, end)
  T Query(int end) const {
    end = min(end, tree_n);
    T sum = T();
    while (end > 0) {
      sum += tree[end];
      end -= (end & -end);
    }
    return sum;
  }
  // Returns the sum of the range [start, tree_n)
  T QuerySuffix(int start) const {
    return tree_sum - Query(start);
  }
  // Returns the sum of the range [start, end)
  T Query(int start, int end) const {
    return Query(end) - Query(start);
  }
  // Returns a[index] in O(1) amortized across every index
  T Get(int index) const {
    assert(0 <= index && index < tree_n);
    int above = index + 1;
    T sum = tree[above];
    above -= (above & -above);
    while (index != above) {
      sum -= tree[index];
      index -= (index & -index);
    }
    return sum;
  }
  bool Set(int index, T value) {
    assert(0 <= index && index < tree_n);
    T current = Get(index);
    if (current == value) return false;
    Update(index, value - current);
    return true;
  }
  static int HighestBit(unsigned x) {
    if (x == 0) return -1;
    return 31 - __builtin_clz(x);
  }
  // Returns largest prefix in [0, tree_n] such that Query(prefix) <= sum.
  // Returns -1 if no such prefix exists (sum < 0).
  int FindLastPrefix(T sum) const {
    if (sum < T()) return -1;
    int prefix = 0;
    for (int k = HighestBit(tree_n); k >= 0; k--) {
      int nxt = prefix + (1 << k);
      if (nxt <= tree_n && tree[nxt] <= sum) {
        sum -= tree[nxt];
        prefix = nxt;
      }
    }
    return prefix;
  }
};