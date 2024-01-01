const int N = 1e5 + 1;  // total de caracteres + 1
const int ALPHABET = 26;
const int C = (int)'a';
struct Trie {
  int trie[N][ALPHABET];
  bool is_terminal[N];
  int nodes = 1;
  void Clear(void) {
    for (int i = 0; i < nodes; i++) {
      is_terminal[i] = false;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) trie[u][c] = nodes++;
      u = trie[u][c];
    }
    is_terminal[u] = true;
  }
  bool IsPrefix(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) return false;
      u = trie[u][c];
    }
    return true;
  }
  bool IsWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) return false;
      u = trie[u][c];
    }
    return is_terminal[u];
  }
} trie;
