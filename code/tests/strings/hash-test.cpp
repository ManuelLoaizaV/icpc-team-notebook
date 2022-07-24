//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2447
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const Long B = 67;
const int N = 2e3 + 10;
const Long C = (Long) '1';

Long Add(Long a, Long b, Long m) { return (a + b) % m; }
Long Mul(Long a, Long b, Long m) { return (a * b) % m; }
Long Sub(Long a, Long b, Long m) { return (a - b + m) % m; }

struct Hash {
  Long mod, base;
  vector<Long> pot;
  vector<Long> h;
  Hash(void) {}
  Hash(Long new_mod = MOD, Long new_base = B, Long new_n = N) {
    mod = new_mod;
    base = new_base;
    h = vector<Long>(new_n); 
    pot = vector<Long>(new_n);
    pot[0] = 1;
    for (int i = 1; i < new_n; i++) pot[i] = Mul(pot[i - 1], base, mod);
  }
  void Build(const string& s) {
    int n = s.size();
    int len = h.size();
    for (int i = 0; i < n; i++) {
      h[i] = s[i] - C + 1;
      if (i > 0) h[i] = Add(h[i], Mul(h[i - 1], base, mod), mod);
    }
  }
  Long Query(int l, int r) {
    if (l == 0) return h[r];
    return Sub(h[r], Mul(h[l - 1], pot[r - l + 1], mod), mod);
  }
};

struct MultiHash {
  vector<Hash> hashes;
  MultiHash(void) {}
  MultiHash(const vector<Long>& mods, const vector<Long>& bases) {
    for (int i = 0; i < mods.size(); i++) hashes.push_back(Hash(mods[i], bases[i]));
  }
  void Build(const string& s) {
    for (int i = 0; i < hashes.size(); i++) hashes[i].Build(s);
  }
  vector<Long> Query(int l, int r) {
    vector<Long> ans;
    for (int i = 0; i < hashes.size(); i++) ans.push_back(hashes[i].Query(l, r));
    return ans;
  }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<Long> GetBases(const vector<Long>& mods) {
  vector<Long> ans;
  for (Long m : mods) {
    Long base = 2LL * random(33, (m - 2) / 2) + 1;
    ans.push_back(base);
  }
  return ans;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  // Hash
  vector<Long> mods = {1000000007, 1000000009};
  vector<Long> bases = GetBases(mods);
  MultiHash multihash(mods, bases);
  // Inicio del programa
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    multihash.Build(s);
    int len = s.size();
    for (int l = 1; l <= len; l++) {
      if (3 * l <= len) continue;
      if (2 * l > len) break;
      if (multihash.Query(0, l - 1) == multihash.Query(l, 2 * l - 1)) {
        if (2 * l < len) {
          int size = len - 2 * l;
          if (multihash.Query(0, size - 1) != multihash.Query(2 * l, 2 * l + size - 1)) continue;
        }
        int ini = len - 2 * l;
        for (int i = 0; i < 8; i++) {
          int pos = (ini + i) % l;
          cout << s[pos];
        }
        cout << "..." << '\n';
        break;
      }
    }
  }
  return 0;
}
