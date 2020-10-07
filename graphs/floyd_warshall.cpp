const int INF = 1e9;
const int N = 1e2, M = 1e4;
int d[N], p[N], u, v, w;
void FloydWarshall() {
  for (int i = 0; i < N; i++) d[i] = INF;
  for (int i = 0; i < N; i++) p[i] = -1;
  for (int i = 0; i < N; i++) d[i][i] = 0;  // Caso base con uno mismo
  for (int i = 0; i < M; i++) {
    cin >> u >> v >> w;  // En este caso es un grafo dirigido, puede no serlo
    d[u][v] = min(d[u][v], w);  // Caso base sin nodos entre ellos
    p[u][v] = u;  // El padre de v respecto a u
  }
  for (int k = 0; k < N; k++) {  // Calculado para nodos <= k en dicho momento
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // dp(i, j, k) = min(dp(i, j, k - 1), dp(i, k, k - 1) + dp(k, j, k - 1))
        // d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        if (d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          p[i][j] = p[k][j];
        }
      }
    }
  }
}
