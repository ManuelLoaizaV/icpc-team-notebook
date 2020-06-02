#include <bits/stdc++.h>
using namespace std;
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

int main() {
	vector<int> a = {2, 3, 10, -1, 8, 3, 2, 100};
	int n = a.size();
	// Creo el segment tree sobre el vector a
	st.build(a, 1, 0, n - 1);
	// Hare consultas 
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			printf("La suma de los elementos desde la posicion %d hasta la posicion %d es %d.\n", i, j, st.query(i, j, 1, 0, n - 1));
	// Hare ciertas modificaciones a algunos elementos
	st.update(3, 50, 1, 0, n - 1);
	st.update(0, -69, 1, 0, n - 1);
	st.update(6, 42, 1, 0, n - 1);
	// De nuevo consultare
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			printf("La suma de los elementos desde la posicion %d hasta la posicion %d es %d.\n", i, j, st.query(i, j, 1, 0, n - 1));
	return 0;
}
