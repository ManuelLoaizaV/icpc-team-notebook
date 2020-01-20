const int N = 1e5;
int tree[4 * N];

void build(int a[], int v, int tl, int tr) {
	if (tl == tr) {
		tree[v] = a[tl];
	} else {
		int tm = (tl + tr) / 2;
		build(a, 2 * v, tl, tm);
		build(a, 2 * v + 1, tm + 1, tr);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
}

int sum(int v, int tl, int tr, int l, int r) {
	if (l > r) return 0;
	if (l == tl and r == tr) return tree[v];
	int tm = (tl + tr) / 2;
	return sum(2 * v, tl, tm, l, min(r, tm)) + sum(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
	if (tl == tr) {
		tree[v] = new_val;
	} else {
		int tm = (tl + tr) / 2;
		if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
		else update(2 * v + 1, tm + 1, tr, pos, new_val);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}
}