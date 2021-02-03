const int N = 1e5, INF = 1e9;
struct SegmentTree {
    multiset<int> t[4 * N];//O(nlgn)
    int cur_val[N];
    int combine(int x, int y) {
        return min(x, y);
    }
    //O(nlg^2(n))
    void build(vector<int> &a, int id, int tl, int tr) {
        if (tl == tr) {
            t[id].insert(a[tl]);
            cur_val[tl] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            t[id] = t[2 * id];
            for (int x : t[2 * id + 1]) t[id].insert(x);
            //t[id].insert(t[2 * id + 1].begin(), t[2 * id + 1].end());
        }
    }
    // O(lg^2(n))
    void update(int pos, int val, int id, int tl, int tr) {
        t[id].erase(t[id].find(cur_val[pos]));
        t[id].insert(val);
        if (tl == tr) {
            cur_val[tl] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(pos, val, 2 * id, tl, tm);
            else update(pos, val, 2 * id + 1, tm + 1, tr);
        }
    }
    //O(lg^2(n))
    int query(int l, int r, int x, int id, int tl, int tr) {
        if (l <= tl and tr <= r) {
            auto it = t[id].lower_bound(x);
            if (it == t[id].end()) return INF;
            else return *it;
        }
        int tm = (tl + tr) / 2;
        if (r <= tm) return query(l, r, x, 2 * id, tl, tm);
        if (tm < l) return query(l, r, x, 2 * id + 1, tm + 1, tr);
        return combine(query(l, r, x, 2 * id, tl, tm), query(l, r, x, 2 * id + 1, tm + 1, tr));
    }
} st;