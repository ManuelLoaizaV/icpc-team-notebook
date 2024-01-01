template<typename T>
vector<T> Compress(const vector<T>& v) {
  int n = (int)v.size();
  vector<pair<T, int>> pairs(n);
  for (int i = 0; i < n; i++) pairs[i] = {v[i], i};
  sort(pairs.begin(), pairs.end());
  vector<T> compressed(n);
  T current = T();
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i - 1].first != pairs[i].second) current++;
    compressed[pairs[i].second] = current;
  }
  return compressed;
}