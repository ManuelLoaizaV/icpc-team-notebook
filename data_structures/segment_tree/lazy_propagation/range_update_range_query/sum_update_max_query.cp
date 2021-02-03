const int N = 1e5;
struct SegmentTree {
    int t[4 * N], lazy[4 * N];
    int combine(int x, int y) { return max(x, y); }
    void build(vector<int> &a, int id, int tl, int tr) {
        lazy[id] = 0;
        if (tl == tr) {
            t[id] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            t[id] = combine(t[2 * id], t[2 * id + 1]);
        }
    }
    void push(int id) {
        // Aplicar lazy al segment tree
        t[2 * id] += lazy[id];
        t[2 * id + 1] += lazy[id];
        // Acumular el lazy
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
        // Reiniciar el lazy
        lazy[id] = 0;
    }
    void update(int l, int r, int add, int id, int tl, int tr) {
        if (tr < l or tl > r) return;
        if (l <= tl and tr <= r) {
            // Aplicar el lazy al nodo
            t[id] += add;
            // Acumular el lazy
            lazy[id] += add;
        } else {
            int tm = (tl + tr) / 2;
            push(id);
            update(l, r, add, 2 * id, tl, tm);
            update(l, r, add, 2 * id + 1, tm + 1, tr);
            t[id] = combine(t[2 * id], t[2 * id + 1]);
        }
    }
    int query(int l, int r, int id, int tl, int tr) {
        if (l <= tl and tr <= r) return t[id];
        int tm = (tl + tr) / 2;
        push(id);
        if (r <= tm) return query(l, r, 2 * id, tl, tm);
        if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
        return combine(query(l, r, 2 * id, tl, tm), query(l, r, 2 * id + 1, tm + 1, tr));   
    }
};