// https://open.kattis.com/problems/generalchineseremainder
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;
typedef tuple<Long, Long, Long> Trio;

Long Mod(__int128 a, Long m) { return ((a % m) + m) % m; }

Long GCD(Long a, Long b) {
  while (b != 0) {
    a = a % b;
    swap(a, b);
  }
  return abs(a);
}

// Solves ax + by = gcd(a, b).
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

// Finds x such that ax = 1 (mod m).
Long Invert(Long a, Long m) {
  assert(GCD(a, m) == 1);
  Long x = Diophantine(a, m, 1LL).first.first;
  return Mod(x, m);
}

// Solves ax = b (mod m).
Pair Solve(Trio equation) {
  Long a = get<0>(equation);
  Long b = get<1>(equation);
  Long m = get<2>(equation);
  Long g = GCD(a, m);
  if (g == 1) return {Mod((__int128)b * Invert(a, m), m), m};
  if (b % g == 0) return Solve(make_tuple(a / g, b / g, m / g));
  return {-1LL, -1LL};
}

// Finds x such that a_i * x = b_i (mod m_i).
// Returns {x, lcm(m_i)} or {-1, -1} if doesn't exist.
Pair CRT(vector<Trio> equations) {
  Long b = 0LL, lcm = 1LL, y, m;
  for (auto equation : equations) {
    tie(y, m) = Solve(equation);  // a_i * y = b_i (mod m)
    if ((b - y) % GCD(lcm, m) != 0) return {-1LL, -1LL};
    if (lcm == m) continue;
    Long k = Diophantine(m, -lcm, b - y).first.second;
    Long new_lcm = lcm * (m / GCD(lcm, m));
    b = Mod((__int128)lcm * k + b, new_lcm);
    lcm = new_lcm;
  }
  return Solve(make_tuple(1LL, b, lcm));
}

void Go(void) {
  vector<Trio> equations;
  for (int i = 0; i < 2; i++) {
    Long a, b, m;
    a = 1LL;
    cin >> b >> m;
    Trio equation = make_tuple(a, b, m);
    equations.push_back(equation);
  }
  Pair crt = CRT(equations);
  if (crt.first == -1 && crt.second == -1) {
    cout << "no solution" << '\n';
  } else {
    cout << crt.first << " " << crt.second << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Go();
  return 0;
}