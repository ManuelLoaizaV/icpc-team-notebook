const int N = 300;
const int INF = 1e9;
int n, w[N][N], d[N][N];

void floyd_warshall(int n) {
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main() {
	for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) w[i][j] = d[i][j] = INF;
	for (int i = 0; i < N; i++) w[i][i] = d[i][i] = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) d[i][j] = w[i][j];
	floyd_warshall(n);
	return 0;
}