const int N = 1e5;
struct SegmentTree {
    int lazy[4 * N];
    bool marked[4 * N];
    void build(vector<int> &a, int id, int tl, int tr) {
        marked[id] = false;
        if (tl == tr) {
            lazy[id] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
        }
    }
    void push(int id) {
        if (marked[id]) {
            int left = 2 * id;
            int right = 2 * id + 1;
            // Asignar
            lazy[left] = lazy[right] = lazy[id];
            marked[left] = marked[right] = true;
            // Reiniciar
            marked[id] = false;
        }
    }
    void update(int l, int r, int val, int id, int tl, int tr) {
        if (tr < l or tl > r) return;
        if (l <= tl and tr <= r) {
            // Asignar
            lazy[id] = val;
            marked[id] = true;
        } else {
            int tm = (tl + tr) / 2;
            push(id);
            update(l, r, val, 2 * id, tl, tm);
            update(l, r, val, 2 * id + 1, tm + 1, tr);
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