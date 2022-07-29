// https://codeforces.com/contest/787/problem/A
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

Long GCD(Long a, Long b) {
  while (b != 0) {
    a = a % b;
    swap(a, b);
  }
  return abs(a);
}

Long LCM(Long a, Long b) {
  return abs(a) / GCD(a, b) * abs(b);
}

// Solves ax + by = gcd(a, b)
Pair Bezout(Long a, Long b) {
  if (b == 0) {
    if (a >= 0) return {1LL, 0LL};
    return {-1LL, 0LL};
  }
  Pair p = Bezout(b, a % b);
  Long x = p.second;
  Long y = p.first - (a / b) * p.second;
  return {x, y};
}

// Solves ax + by = r.
// Solutions exist iff gcd(a, b) = d | r.
// Solutions are given by {p + t * (-b/d, a/d)}.
pair<Pair, Pair> Diophantine(Long a, Long b, Long r) {
  Long d = GCD(a, b);
  assert(r % d == 0);
  Long _a = a / d, _b = b / d, _r = r / d;
  Pair p = Bezout(_a, _b);
  p.first *= _r, p.second *= _r;
  assert(_a * p.first + _b * p.second == _r);
  return {p, {-_b, _a}};
}

// Floor and ceiling functions
bool SameSign(Long a, Long b) {
  return a > 0 && b > 0 || a < 0 && b < 0;
}

Long Floor(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (SameSign(a, b)) return abs(a) / abs(b);
  return (-1LL) * (1LL + (abs(a) - 1) / abs(b));
}

Long Ceiling(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (!SameSign(a, b)) return (-1LL) * (abs(a) / abs(b));
  return 1LL + (abs(a) - 1LL) / abs(b);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<Long> n(4);
  for (int i = 0; i < 4; i++) cin >> n[i];

  Long a = n[0];
  Long b = -n[2];
  Long r = n[3] - n[1];

  Long d = GCD(a, b);

  if (r % d != 0) {
    cout << -1 << '\n';
    return 0;
  }

  auto solutions = Diophantine(a, b, r);
  Pair base = solutions.first;
  Pair delta = solutions.second;
  Long t = max(Ceiling(-base.first, delta.first), Ceiling(-base.second, delta.second));
  Long x = base.first + t * delta.first;
  Long ans = n[1] + x * n[0];
  cout << ans << '\n';
  return 0;
}