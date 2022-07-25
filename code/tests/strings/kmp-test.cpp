// https://codeforces.com/contest/432/problem/D
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int A = 26;
const int C = 'A';

vector<int> CalculatePi(const string& s) {
  int n = (int)s.size();
  vector<int> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

const int N = 1e5 + 5;

vector<int> adj[N];
int cnt[N];

int DFS(int u) {
  for (int v : adj[u]) {
    cnt[u] += DFS(v);
  }
  return cnt[u];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;

  vector<int> pi = CalculatePi(s);

  int n = (int)s.size();

  vector<int> prefixes;
  int prefix_len = n;
  while (prefix_len > 0) {
    prefixes.push_back(prefix_len);
    prefix_len = pi[prefix_len - 1];
  }
  reverse(prefixes.begin(), prefixes.end());

  for (int i = 0; i < n; i++) {
    cnt[pi[i]]++;
    adj[pi[i]].push_back(i + 1);
  }
  DFS(0);

  int n_prefixes = (int)prefixes.size();
  cout << n_prefixes << '\n';
  for (int i = 0; i < n_prefixes; i++) {
    cout << prefixes[i] << " " << 1 + cnt[prefixes[i]] << '\n';
  }
  return 0;
}