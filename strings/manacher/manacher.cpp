// d1[i]: number of odd palindromes centered at i
// d2[i]: number of even palindromes centered at [i - 1, i]
void Manacher(const string& s, vector<Long>& d1, vector<Long>& d2) {
  Long n = s.size();
  d1 = vector<Long>(n, 0);
  d2 = vector<Long>(n, 0);
  int l = 0; r = -1;
  for (int i = 0; i < n; i++) {
    d1[i] = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) d1[i]++;
    if (i + d1[i] - 1 > r) {
      l = i - d1[i] + 1;
      r = i + d1[i] - 1;
    }
  }
  l = 0; r = -1;
  for (int i = 0; i < n; i++) {
    d2[i] = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - d2[i] - 1 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]]) d2[i]++;
    if (i + d2[i] - 1 > r) {
      l = i - d2[i];
      r = i + d2[i] - 1;
    }
  }
}
