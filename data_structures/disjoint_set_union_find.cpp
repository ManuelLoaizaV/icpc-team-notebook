const int N = 1e5;
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