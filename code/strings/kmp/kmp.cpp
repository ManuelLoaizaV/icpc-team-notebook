const int A = 26;
const int C = 'a';
vector<int> CalculatePi(const string& s) {
  int n = (int) s.size();
  vector<int> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<vector<int>> CalculateAutomata(const string& s, const vector<int>& pi) {
  int n = (int) s.size();
  vector<vector<int>> go(n + 1, vector<int> (A, 0));
  go[0][s[0] - C] = 1;
  for (int pos = 1; pos <= n; pos++) {
    for (int chr = 0; chr < A; chr++) {
      if (pos < n && (chr == (s[pos] - C))) {
        go[pos][chr] = pos + 1;
      } else {
        go[pos][chr] = go[pi[pos - 1]][chr];
      }
    }
  }
  return go;
}
