typedef vector<vector<long long>> Matrix;
Matrix I(int n) {
	Matrix ans(n, vector<long long>(n));
	for (int i = 0; i < n; i++) ans[i][i] = 1;
	return ans;
}
Matrix operator * (Matrix &a, Matrix &b) {
	int n = a.size();
	int m = a[0].size();
	int p = b[0].size();
	Matrix ans(n, vector<long long>(p));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
			for (int k = 0; k < m; k++)
				ans[i][j] += a[i][k] * b[k][p];
	return ans;
}
Matrix fast_pow(Matrix a, long long b) {
	Matrix ans = I(a.size());
	while (b > 0) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;	
}