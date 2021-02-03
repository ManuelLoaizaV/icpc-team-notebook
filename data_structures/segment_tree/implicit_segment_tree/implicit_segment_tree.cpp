struct Node {
  Long sum, lazy;
  Node* left;
  Node* right;
  Node(void) : sum(0), lazy(0), left(nullptr), right(nullptr) {}
  void Push(Long tl, Long tr) {
    if (left == nullptr) {
      left = new Node();
      right = new Node();
    }
    Long tm = (tl + tr) / 2;
    Long left_size = tm - tl + 1;
    Long right_size = tr - tm;
    // Aplicar
    left->sum += left_size * lazy;
    right->sum += right_size * lazy;
    // Propagar
    left->lazy += lazy;
    right->lazy += lazy;
    // Reiniciar
    lazy = 0;
  }
};
struct SegmentTree {
  Node* root;
  Long n;
  SegmentTree(void) {}
  SegmentTree(Long m) {
    root = new Node();
    n = m;
  }
  Long Merge(Long x, Long y) { return x + y; }
  void Update(Long l, Long r, Long val, Node* node, Long tl, Long tr) {
    if (r < tl || l > tr) return;
    if (l <= tl && tr <= r) {
      // Aplicar
      node->sum += (tr - tl + 1) * val;
      // Acumular
      node->lazy += val;
    } else {
      Long tm = (tl + tr) / 2;
      node->Push(tl, tr);
      Update(l, r, val, node->left, tl, tm);
      Update(l, r, val, node->right, tm + 1, tr);
      node->sum = Merge(node->left->sum, node->right->sum);
    }
  }
  Long Query(Long l, Long r, Node* node, Lont tl, Long tr) {
    if (l <= tl && tr <= r) return node->sum;
    Long tm = (tl + tr) / 2;
    node->Push(tl, tr);
    if (r <= tm) return Query(l, r, node->left, tl, tm);
    if (tm < l) return Query(l, t, node->right, tm + 1, tr);
    return Merge(Query(l, r, node->left, tl, tm), Query(l, r, node->right, tm + 1, tr));
  }
} st;
