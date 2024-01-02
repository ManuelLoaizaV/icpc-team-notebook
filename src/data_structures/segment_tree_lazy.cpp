struct SegmentChange {
  static const int SENTINEL = numeric_limits<int>::lowest();
  int to_set, to_add;
  // Make sure the default constructor is the identity SegmentChange
  SegmentChange(int _to_set = SENTINEL, int _to_add = 0) : to_set(_to_set), to_add(_to_add) {}
  bool HasSet(void) const { return to_set != SENTINEL; }
  bool HasChange(void) const { return HasSet() || to_add != 0; }
  void Merge(const SegmentChange &other) {
    if (other.HasSet()) return;
    to_add += other.to_add;
    to_set = other.to_set;
  }
};
struct Segment {
  int maximum;
  int64_t sum;
  Segment(int _maximum = numeric_limits<int>::lowest(), int64_t _sum = 0) : maximum(_maximum), sum(_sum) {}
  void Merge(const Segment &other) {
    maximum = max(maximum, other.maximum);
    sum += other.sum;
  }
  void Merge(const Segment &left, const Segment &right) {
    *this = left;
    Merge(right);
  }
  void Apply(int start, int end, const SegmentChange &change) {
    int64_t length = end - start + 1LL;
    if (change.HasSet()) {
      maximum = change.to_set;
      sum = length * change.to_set;
    }
    maximum += change.to_add;
    sum += length * change.to_add;
  }
};
struct SegmentTree {
  int initial_n = 0;
  int tree_n = 0;
  vector<Segment> tree;
  vector<SegmentChange> changes;
  SegmentTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    initial_n = n;
    tree_n = 2 * initial_n;
    tree.assign(tree_n, Segment());
    changes.assign(tree_n, SegmentChange());
  }
  void Build(const vector<Segment> &initial, int segment_id, int start, int end) {
    if (start == end) {
      tree[segment_id].Merge(initial[start]);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Build(initial, left_segment_id, start, mid);
    Build(initial, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Build(const vector<Segment> &initial) { // O(n)
    int n = (int)initial.size();
    Init(n);
    Build(initial, 1, 0, n - 1);
  }
  void ApplyAndMerge(int segment_id, int start, int end, const SegmentChange &change) {
    tree[segment_id].Apply(start, end, change);
    changes[segment_id].Merge(change);
  }
  void Push(int segment_id, int start, int end) {
    if (!changes[segment_id].HasChange()) return;
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    ApplyAndMerge(left_segment_id, start, mid, changes[segment_id]);
    ApplyAndMerge(right_segment_id, mid + 1, end, changes[segment_id]);
    changes[segment_id] = SegmentChange();
  }
  Segment Query(int query_start, int query_end, int segment_id, int start, int end) {
    if (query_start <= start && end <= query_end) return tree[segment_id];
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    if (query_end <= mid) return Query(query_start, query_end, left_segment_id, start, mid);
    if (mid < query_start) return Query(query_start, query_end, right_segment_id, mid + 1, end);
    Segment response = Query(query_start, query_end, left_segment_id, start, mid);
    response.Merge(Query(query_start, query_end, right_segment_id, mid + 1, end));
    return response;
  }
  Segment Query(int query_start, int query_end) { return Query(query_start, query_end, 1, 0, initial_n - 1); }
  Segment QueryFull(void) { return tree[1]; }
  void Update(int update_start, int update_end, const SegmentChange &change, int segment_id, int start, int end) {
    if (end < update_start || update_end < start) return;
    if (update_start <= start && end <= update_end) {
      ApplyAndMerge(segment_id, start, end, change);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    Update(update_start, update_end, change, left_segment_id, start, mid);
    Update(update_start, update_end, change, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Update(int update_start, int update_end, const SegmentChange &change) { Update(update_start, update_end, change, 1, 0, initial_n - 1); }
};
