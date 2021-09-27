const int N = 1e5 + 1;  // total de caracteres + 1
const int ALPHABET = 26;
const int C = (int)'a';
struct Trie {
  map<int, int> trie[N];
  int cnt[N];
  bool is_terminal[N];
  int nodes = 1;
  void Clear(void) {
    for (int i = 0; i < nodes; i++) {
      is_terminal[i] = false;
      trie[i].clear();
      cnt[i] = 0;
    }
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) trie[u][c] = nodes++;
      u = trie[u][c];
      cnt[u]++;
    }
    is_terminal[u] = true;
  }
  void DeleteWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      int next_u = trie[u][c];
      cnt[next_u]--;
      if (cnt[next_u] == 0) trie[u].erase(c);
      u = next_u;
    }
    is_terminal[u] = false;
  }
  bool IsPrefix(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
    }
    return true;
  }
  bool IsWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
    }
    return is_terminal[u];
  }
} trie;
