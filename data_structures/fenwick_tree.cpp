const int N = 10;
int tree[N + 5];
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