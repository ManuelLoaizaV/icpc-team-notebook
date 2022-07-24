#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

Long GCD(Long a, Long b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

// Find x, y such that ax + by = (a, b)
Pair ExtendedEuclidean(Long a, Long b) {
  if (b == 0) return {1, 0};
  Pair p = ExtendedEuclidean(b, a % b);
  Long x = p.second;
  Long y = p.first - (a / b) * x;
  if (a * x + b * y == -GCD(a, b)) {
    x = -x;
    y = -y;
  }
  return {x, y};
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long n, m, a, k;
  while (cin >> n >> m >> a >> k) {
    if (n == 0 && m == 0 && a == 0 && k == 0) break;
    
  }
  return 0;
}