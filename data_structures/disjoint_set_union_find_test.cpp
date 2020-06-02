#include <bits/stdc++.h>
using namespace std;
const int N = 10;

struct DSU {
	int parent[N + 1];
	// Crea un nuevo set que consiste del nuevo elemento v
	void make_set(int v) { parent[v] = v; }
	// Retorna el representante del set que contiene al elemento v
	int find_set(int u) {
		if (parent[u] == u) return u;
		parent[u] = find_set(parent[u]);
		return parent[u];
	}
	// Chequea si dos elementos son parte del mismo set o no
	bool same_set(int u, int v) {
		return find_set(u) == find_set(v);
	}
	// Une los sets en los cuales u y v se encuentran
	void union_sets(int u, int v) {
		int p_u = find_set(u);
		int p_v = find_set(v);
		if (p_u != p_v) parent[p_v] = p_u;
	}
} dsu;

int main() {
	// Supongamos que quiero crear estas 4 componentes
	// (1, 2, 3) (4, 5) (6, 7, 8, 9) (10)
	for (int i = 1; i <= N; i++) dsu.make_set(i);
	dsu.union_sets(1, 2);
	dsu.union_sets(2, 3);
	dsu.union_sets(4, 5);
	dsu.union_sets(6, 7);
	dsu.union_sets(6, 8);
	dsu.union_sets(9, 8);
	// Chequeare a que componente pertenece cada elemento
	for (int i = 1; i <= N; i++)
		printf("El elemento %d pertenece a la componente representada por %d.\n", i, dsu.find_set(i));
	// Chequeare todos los pares
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (dsu.same_set(i, j)) printf("%d y %d se encuentran en el mismo set.\n", i, j);
			else printf("%d y %d no se encuentran en el mismo set.\n", i, j);
	return 0;
}
