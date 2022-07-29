#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;
typedef tuple<Long, Long, Long> Trio;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
// find_by_order(k): Returns an iterator to the k-th largest element (0 indexed).
// order_of_key(k): Returns the number of items that are stricly smaller than k.

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Long GetRandom(Long l, Long r) {
  return uniform_int_distribution<Long>(l, r)(rng);
}

vector<Long> GetPermutation(int n) {
  vector<Long> permutation(n);
  for (int i = 0; i < n; i++) permutation[i] = i;
  shuffle(permutation.begin(), permutation.end(), rng);
  return permutation;
}

Long GetBit(Long mask, Long bit) { return (mask >> bit) & 1LL; }

void TurnOn(Long& mask, Long bit) { mask = mask | (1LL << bit); }

void TurnOff(Long& mask, Long bit) { mask = mask & (~(1 << bit)); }

void Solve(void) {
  
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}