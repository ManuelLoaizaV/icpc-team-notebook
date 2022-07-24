#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const Long INF = 1e18;
const Double EPS = 1e-9;
const int LEN = 19;
const int N = 2e7 + 1;  // CUIDADO 19 * 10 ^ 6 pero no usare todos
const int ALPHABET = 10;

struct Trie {
  int trie[N][ALPHABET];
  bool is_terminal[N];
  int nodes = 1;
  void Build(void) {
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
      int c = s[i] - '0';
      if (trie[u][c] == 0) trie[u][c] = nodes++;
      u = trie[u][c];
    }
    is_terminal[u] = true;
  }
  string GetMin(const string& s) {
    int n = s.size();
    int u = 0;
    string answer = "";
    for (int i = 0; i < n; i++) {
      int c = s[i] - '0';
      int best = 10 - c;
      bool found = false;
      for (int d = best; d <= 9; d++) {
        if (trie[u][d] != 0) {
          answer += char('0' + (c + d) % 10);
          u = trie[u][d];
          found = true;
          break;
        }
      }
      if (!found) {
        for (int d = 0; d < best; d++) {
          if (trie[u][d] != 0) {
            answer += char('0' + (c + d) % 10);
            u = trie[u][d];
            break;
          }
        }
      }
      //debug(answer);
    }
    return answer;
  }
  string GetMax(const string& s) {
    int n = s.size();
    int u = 0;
    string answer = "";
    for (int i = 0; i < n; i++) {
      int c = s[i] - '0';
      int best = 9 - c;
      bool found = false;
      for (int d = best; d >= 0; d--) {
        if (trie[u][d] != 0) {
          answer += char('0' + (c + d) % 10);
          u = trie[u][d];
          found = true;
          break;
        }
      }
      if (!found) {
        for (int d = 9; d > best; d--) {
          if (trie[u][d] != 0) {
            answer += char('0' + (c + d) % 10);
            u = trie[u][d];
            break;
          }
        }
      }
      //debug(answer);
    }
    return answer;
  }
} trie;

string GetString(string s) {
  string answer;
  for (int i = 0; i < LEN; i++) answer += '0';
  int len = s.size();
  for (int i = 0; i < len; i++) answer[LEN - 1 - i] = s[len - 1 - i];
  return answer;
}

Long StringToLong(const string& s) {
  Long answer = 0;
  Long pot = 1LL;
  for (int i = 0; i < LEN; i++) {
    Long digit = s[LEN - 1 - i] - '0';
    answer += pot * digit;
    pot *= 10LL;
  }
  return answer;
}

void Solve(void) {
  int n;
  cin >> n;
  string minimum, maximum;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    s = GetString(s);
    if (i > 0) {
      string current_minimum = trie.GetMin(s);
      string current_maximum = trie.GetMax(s);
      //debug(s, current_minimum, current_maximum);
      if (i == 1) {
        minimum = current_minimum;
        maximum = current_maximum;
      } else {
        if (current_minimum < minimum) minimum = current_minimum;
        if (current_maximum > maximum) maximum = current_maximum;
      }
    }
    trie.AddWord(s);
  }
  cout << StringToLong(minimum) << " " << StringToLong(maximum) << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

