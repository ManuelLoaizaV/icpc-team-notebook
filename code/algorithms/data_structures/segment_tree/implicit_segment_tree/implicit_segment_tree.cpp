const Long N = 1e9;
struct Node {
  Long sum;
  bool lazy;
  Node* left;
  Node* right;
  Node(void) {
    sum = 0;
    lazy = false;
    left = right = nullptr;
  }
  void Push(Long tl, Long tr) {
    if (left == nullptr) {
      left = new Node();
      right = new Node();
    }
    if (lazy) {
      // Aplicar
      Long tm = (tl + tr) / 2;
      left->sum = tm - tl + 1;
      right->sum = tr - tm;
      // Propagar
      left->lazy = true;
      right->lazy = true;
      // Reiniciar
      lazy = false;
    }
  }
};
struct SegmentTree {
  Node* root;
  Long n;
  SegmentTree(void) {}
  SegmentTree(Long new_n) {
    root = new Node();
    n = new_n;
  }
  Long Merge(const Long& x, const Long& y) { return x + y; }
  void Update(Long l, Long r, Long val, Node* node, Long tl, Long tr) {
    if (r < tl || l > tr) return;
    if (l <= tl && tr <= r) {
      // Aplicar
      node->sum = (tr - tl + 1) * val;
      // Acumular
      node->lazy = true;
    } else {
      Long tm = (tl + tr) / 2;
      node->Push(tl, tr);
      Update(l, r, val, node->left, tl, tm);
      Update(l, r, val, node->right, tm + 1, tr);
      node->sum = Merge(node->left->sum, node->right->sum);
    }
  }
  void Update(Long l, Long r, Long val) { Update(l, r, val, root, 0, n - 1); }
  Long Query(Long l, Long r, Node* node, Long tl, Long tr) {
    if (l <= tl && tr <= r) return node->sum;
    Long tm = (tl + tr) / 2;
    node->Push(tl, tr);
    if (r <= tm) return Query(l, r, node->left, tl, tm);
    if (tm < l) return Query(l, r, node->right, tm + 1, tr);
    return Merge(Query(l, r, node->left, tl, tm), Query(l, r, node->right, tm + 1, tr));
  }
  Long Query(Long l, Long r) { return Query(l, r, root, 0, n - 1); }
};
