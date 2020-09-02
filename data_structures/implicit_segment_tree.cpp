struct Node {
    int sum, lazy;
    Node* left;
    Node* right;
    Node() : sum(0), lazy(0), left(nullptr), right(nullptr) {}
    void push(int tl, int tr) {
        if (left == nullptr) {
            left = new Node();
            right = new Node();
        }
        int tm = (tl + tr) / 2;
        int left_size = tm - tl + 1;
        int right_size = tr - tm;
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
    SegmentTree() { root = new Node(); }
    int combine(int x, int y) { return x + y; }
    void update(int l, int r, int val, Node* node, int tl, int tr) {
        if (r < tl or l > tr) return;
        if (l <= tl and tr <= r) {
            // Aplicar
            node->sum += (tr - tl + 1) * val;
            // Acumular
            node->lazy += val;
        } else {
            int tm = (tl + tr) / 2;
            node->push(tl, tr);
            update(l, r, val, node->left, tl, tm);
            update(l, r, val, node->right, tm + 1, tr);
            node->sum = combine(node->left->sum, node->right->sum);
        }
    }
    int query(int l, int r. Node* node, int tl, int tr) {
        if (l <= tl and tr <= r) return node->sum;
        int tm = (tl + tr) / 2;
        node->push(tl, tr);
        if (r <= tm) return query(l, r, node->left, tl, tm);
        if (tm < l) return query(l, r, node->right, tm + 1, tr);
        return combine(query(l, r, node->left, tl, tm), query(l, r, node->right, tm + 1, tr));
    }
} st;