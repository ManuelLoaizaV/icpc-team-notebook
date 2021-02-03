const int N = 1e5;
struct SegmentTree {
    int lazy[4 * N];
    void build(vector<int> &a, int id, int tl, int tr) {
        if (tl == tr) {
            lazy[id] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            lazy[id] = 0;
        }
    }
    void push(int id) {
        // Agregar
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
        // Reiniciar
        lazy[id] = 0;
    }
    void update(int l, int r, int add, int id, int tl, int tr) {
        if (tr < l or tl > r) return;
        if (l <= tl and tr <= r) {
            // Agregar
            lazy[id] += add;
        } else {
            int tm = (tl + tr) / 2;
            push(id);
            update(l, r, add, 2 * id, tl, tm);
            update(l, r, add, 2 * id + 1, tm + 1, tr);
        }
    }
    int query(int pos, int id, int tl, int tr) {
        if (tl == tr) return lazy[id];
        int tm = (tl + tr) / 2;
        push(id);
        if (pos <= tm) return query(pos, 2 * id, tl, tm);
        else return query(pos, 2 * id + 1, tm + 1, tr);
    }
};