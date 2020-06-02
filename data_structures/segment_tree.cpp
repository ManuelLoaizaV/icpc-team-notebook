const int N = 1e5;
struct SegmentTree {
	int tree[4 * N];	
	void build(vector<int> &a, int id, int tl, int tr) {
		if (tl == tr) {
			tree[id] = a[tl];
		} else {
			int tm = (tl + tr) / 2;
			build(a, 2 * id, tl, tm);
			build(a, 2 * id + 1, tm + 1, tr);
			tree[id] = tree[2 * id] + tree[2 * id + 1];
		}
	}
	void update(int pos, int val, int id, int tl, int tr) {
		if (tl == tr) {
			tree[pos] = val;
		} else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) update(pos, val, 2 * id, tl, tm);
			else update(pos, val, 2 * id + 1, tm + 1, tr);
			tree[id] = tree[2 * id] + tree[2 * id + 1];
		}
	}
	int query(int l, int r, int id, int tl, int tr) {
		if (l <= tl and tr <= r) return tree[id];
		int tm = (tl + tr) / 2;
		if (r <= tm) return query(l, r, 2 * id, tl, tm);
		if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
		return query(l, r, 2 * id, tl, tm) + query(l, r, 2 * id + 1, tm + 1, tr);
	}
} st;