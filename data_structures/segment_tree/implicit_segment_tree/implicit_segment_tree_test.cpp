#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long Long;
const Long N = 1e2;

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
  SegmentTree(void) { root = new Node(); }
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
  Long Query(Long l, Long r, Node* node, Long tl, Long tr) {
    if (l <= tl && tr <= r) return node->sum;
    Long tm = (tl + tr) / 2;
    node->Push(tl, tr);
    if (r <= tm) return Query(l, r, node->left, tl, tm);
    if (tm < l) return Query(l, r, node->right, tm + 1, tr);
    return Merge(Query(l, r, node->left, tl, tm), Query(l, r, node->right, tm + 1, tr));
  }
};

void Solve(void) {
  Long n, q;
  cin >> n >> q;
  SegmentTree st;
  while (q--) {
    Long t, l, r;
    cin >> t >> l >> r;
    l--;
    r--;
    if (t == 0) {
      Long v;
      cin >> v;
      st.Update(l, r, v, st.root, 0, N - 1);
    } else {
      cout << st.Query(l, r, st.root, 0, N - 1) << endl;
    }
  }
}

int main() {
  fastio;
  Long t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
