#include <bits/stdc++.h>
using namespace std;
const int N = 10;

struct FenwickTree {
	int tree[N + 5];
	void build(int n) { for (int i = 0; i <= n; i++) tree[i] = 0; }
	// Suma delta a todos los elementos en el rango [i, N]
	void update(int i, int delta) {
		while (i <= N) {
			tree[i] += delta;
			i += (i & -i);
		}
	}
	// Halla la suma acumulada en la posicion i
	int query(int i) {
		int ret = 0;
		while (i > 0) {
			ret += tree[i];
			i -= (i & -i);
		}
		return ret;
	}
} ft;

int main() {
	ft.build(N);
	ft.update(2, 1);
	ft.update(4, 1);
	ft.update(6, 1);
	ft.update(9, 1);
	ft.update(10, 1);
	for (int i = 1; i <= N; i++) printf("Hay %d elementos menores o iguales a %d.\n", ft.query(i), i);
	return 0;
}
