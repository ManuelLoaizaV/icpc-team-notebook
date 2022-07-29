#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

bool EqualSign(Long a, Long b) {
  return a > 0 && b > 0 || a < 0 && b < 0;
}

Long FloorDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (EqualSign(a, b)) return abs(a) / abs(b);
  return (-1LL) * (1LL + (abs(a) - 1) / abs(b));
}

Long CeilDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (!EqualSign(a, b)) return (-1LL) * (abs(a) / abs(b));
  return 1LL + (abs(a) - 1LL) / abs(b);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // Floor division
  assert(FloorDiv(20, 6) == 3);
  assert(FloorDiv(-20, -6) == 3);
  assert(FloorDiv(-20, 6) == -4);
  assert(FloorDiv(20, -6) == -4);
  // Ceil division
  assert(CeilDiv(20, 6) == 4);
  assert(CeilDiv(-20, -6) == 4);
  assert(CeilDiv(-20, 6) == -3);
  assert(CeilDiv(20,- 6) == -3);
  return 0;
}