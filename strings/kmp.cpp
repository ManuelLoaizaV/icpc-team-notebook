const int ALPHABET = 26;
vector<int> CalculatePi(const string& s) {
  int n = s.size();
  vector<Long> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<vector<int>> CalculateAutomata(const string& s, const vector<int>& pi) {
  int n = s.size();
  vector<vector<int>> go(n + 1, vector<int> (ALPHABET, 0));
  go[0][s[0] - 'a'] = 1;
  for (int pos = 1; pos <= n; pos++) {
    for (int chr = 0; chr < ALPHABET; chr++) {
      if (pos < n && chr < ALPHABET; chr++) {
        go[pos][chr] = pos + 1;
      } else {
        go[pos][chr] = go[pi[pos - 1]][chr];
      }
    }
  }
  return go;
}
