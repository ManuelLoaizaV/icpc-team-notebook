const int ALPHABET = 26;
const int N = 2e5 + 1;  // total de caracteres + 1
const int C = (int) 'a';
struct Trie {
  int trie[N][ALPHABET];
  bool is_end[N];
  int fail[N];
  int fail_out[N];
  int nodes;
  void Clear(void) {
    for (int i = 0; i < nodes; i++) {
      is_end[i] = false;
      fail[i] = 0;
      fail_out[i] = 0;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }
  void Build(void) {
    queue<int> q;
    q.push(0);
    while (q.size() > 0) {
      int from = q.front();
      q.pop();
      for (int c = 0; c < ALPHABET; c++) {
        int to = trie[from][c];
        if (to == 0) continue;
        q.push(to);
        if (from == 0) continue;
        fail[to] = fail[from];
        while (fail[to] > 0 && trie[fail[to]][c] == 0) fail[to] = fail[fail[to]];
        fail[to] = trie[fail[to]][c];
        fail_out[to] = is_end[fail[to]] ? fail[to] : fail_out[fail[to]];
      }
    }
  }
  void AddWord(const string& s) {
    int from = 0;
    for (char c : s) {
      int to = c - C;
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
    }
    is_end[from] = true;
  }
  bool IsEnd(int u) { return is_end[u]; }
  int GetFail(int u) { return fail[u]; }
  int GetFailOut(int u) { return fail_out[u]; }
  int GetNode(int u, int v) { return trie[u][v]; }
} aho;
// IMPORTANTE: Limpiar, añadir palabras y construir
void Solve(const string& s) {
  int from = 0;
  for (int i = 0; i < len; i++) {
    int to = s[i] - C;
    while (from > 0 && aho.GetNode(from, to) == 0) from = aho.GetFail(from);
    from = aho.GetNode(from, to);
    int back = from;
    while (back > 0) {
      if (aho.IsEnd(back)) {
        // Analizamos todos los fin de palabra que terminan en s[i]
      }
      back = aho.GetFailOut(back);
    }
  }
}