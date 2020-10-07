const int INF = 1e9;
const int N = 5e2;
struct Edge { int u, v, w; };
vector<Edge> edges;
int d[N];
void BellmanFord(int s) {
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = 0;
  // Numero de iteraciones que vamos a hacer del algoritmo
  for (int i = 0; i < N - 1; i++) {
    for (Edge e : edges) {
      d[e.v] = min(d[e.v], d[e.u] + e.w);
    }
  }
  // Determinar ciclos negativos
  for (Edge e : edges) {
    if (d[e.u] + e.w < d[e.v]) {
      cout << "Ciclo negativo encontrado." << '\n';
      return;
    }
  }
}
