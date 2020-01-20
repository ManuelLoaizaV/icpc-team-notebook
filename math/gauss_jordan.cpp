// O(n^3)
// a : matriz con los coeficientes del sistema lineal de n ecuaciones con m incognitas
// 0 : No hay solucion
// 1 : Solucion unica
// INF : Infinitas soluciones
// Si al menos una solucion existe, la retorna en ans
int gauss_jordan(vector<vector<long double>> a, vector<long double> &ans) {
	int n = a.size();
	int m = a[0].size() - 1;
	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m and row < n; col++) {
		int sel = row;
		for (int i = row; i < n; i++) if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
		if (abs(a[sel][col]) < EPS) continue;
		for (int i = col; i <= m; i++) swap(a[sel][i], a[row][i]);
		where[col] = row;
		for (int i = 0; i < n; i++) {
			if (i != row) {
				long double c = a[i][col] / a[row][col];
				for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
			}
		}
		row++;
	}
	ans.assign(m, 0);
	for (int i = 0; i < n; i++) if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i = 0; i < n; i++) {
		long double sum = 0.0;
		for (int j = 0; j < m; j++) sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m]) > EPS) return 0;
	}
	for (int i = 0; i < m; i++) if (where[i] == -1) return INF;
	return 1;
}