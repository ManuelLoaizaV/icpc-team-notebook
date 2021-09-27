// https://codeforces.com/problemset/problem/1080/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 250;
const int A = 26;
const Long MOD = 1e9 + 7;
const Pair BAN = {-1, -1};
vector<vector<Long>> frequency;
vector<Long> odd;

// d1[i]: number of odd palindromes centered at i
// d2[i]: number of even palindromes centered at [i - 1, i]
Long Manacher(int left, int right) {
  int n = right - left + 1;
  vector<Long> d1(n, 0);
  vector<Long> d2(n, 0);
  int l = 0;
  int r = -1;
  for (int i = 0; i < n; i++) {
    d1[i] = (i > r) ? 1 : min(d1[l + r - i], r - i + 1LL);
    while (0 <= i - d1[i] && i + d1[i] < n && frequency[left + i - d1[i]] == frequency[left + i + d1[i]]) d1[i]++;
    if (i + d1[i] - 1 > r) {
      l = i - d1[i] + 1;
      r = i + d1[i] - 1;
    }
  }
  l = 0; r = -1;
  for (int i = 0; i < n; i++) {
    d2[i] = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1LL);
    while (0 <= i - d2[i] - 1 && i + d2[i] < n && frequency[left + i - d2[i] - 1] == frequency[left + i + d2[i]]) d2[i]++;
    if (i + d2[i] - 1 > r) {
      l = i - d2[i];
      r = i + d2[i] - 1;
    }
  }
  Long answer = 0;
  for (int i = 0; i < n; i++) answer += d1[i] + d2[i];
  return answer;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<string> s(n);
  for (int i = 0; i < n; i++) cin >> s[i];
  Long answer = 0;
  // Para cada par de columnas
  for (int left = 0; left < m; left++) {
    frequency.assign(n, vector<Long>(26, 0));
    odd.assign(n, 0);
    for (int right = left; right < m; right++) {
      // Para cada fila, hallo las frecuencias de los caracteres
      for (int row = 0; row < n; row++) {
        frequency[row][s[row][right] - 'a']++;
        if (frequency[row][s[row][right] - 'a'] & 1) {
          odd[row]++;
        } else {
          odd[row]--;
        }
      }
      // Creo todos los pares consecutivos
      for (int row = 0; row < n; row++) {
        if (odd[row] < 2) {
          int l = row;
          int r = l;
          while (r < n && odd[r] < 2) r++;
          r--;
          answer += Manacher(l, r);
          row = r;
        }
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
