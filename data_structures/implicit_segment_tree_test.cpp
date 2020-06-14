#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
#define For(i,a,b) for (Long i = a; i < b; i++)
using namespace std;
typedef long long Long;
const Long N = 1e9;

struct Node {
    Long sum, lazy;
    Node* left;
    Node* right;
    Node() : sum(0), lazy(0), left(nullptr), right(nullptr) {}
    void push(Long tl, Long tr) {
        if (left == nullptr) {
            left = new Node();
            right = new Node();
        }
        Long tm = (tl + tr) / 2;
        Long left_size = tm - tl + 1;
        Long right_size = tr - tm;
        // Aplico
        left->sum += left_size * lazy;
        right->sum += right_size * lazy;
        // Propago
        left->lazy += lazy;
        right->lazy += lazy;
        // Reinicio
        lazy = 0;
    }
};

struct SegmentTree {
    Node* root;
    SegmentTree() { root = new Node(); }
    Long combine(Long x, Long y) { return x + y; }
    void update(Long l, Long r, Long val, Node* node, Long tl, Long tr) {
        if (r < tl or l > tr) return;
        if (l <= tl and tr <= r) {
            // Aplico
            Long sz = tr - tl + 1;
            node->sum += val * sz;
            // Acumulo
            node->lazy += val;
        } else {
            Long tm = (tl + tr) / 2;
            node->push(tl, tr);
            update(l, r, val, node->left, tl, tm);
            update(l, r, val, node->right, tm + 1, tr);
            node->sum = combine(node->left->sum, node->right->sum);
        }
    }
    Long query(Long l, Long r, Node* node, Long tl, Long tr) {
        if (l <= tl and tr <= r) return node->sum;
        Long tm = (tl + tr) / 2;
        node->push(tl, tr);
        if (r <= tm) return query(l, r, node->left, tl, tm);
        if (tm < l) return query(l, r, node->right, tm + 1, tr);
        return combine(query(l, r, node->left, tl, tm), query(l, r, node->right, tm + 1, tr));
    }
};

void solve() {
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
            st.update(l, r, v, st.root, 0, N - 1);
        } else  {
            cout << st.query(l, r, st.root, 0, N - 1) << endl;
        }
    }
}

int main() {
    fastio;
    Long t;
    cin >> t;
    while (t--) solve();
    return 0;
}