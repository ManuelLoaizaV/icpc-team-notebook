// https://open.kattis.com/problems/generalchineseremainder
#include <bits/stdc++.h>
using namespace std;
typedef long long Long;
typedef pair<Long, Long> Pair;
typedef tuple<Long, Long, Long> Trio;

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

// Find all solutions to ax + by = c
// where (a, b) | c
pair<Pair, Pair> LinearDiophantine(Long a, Long b, Long c) {
  Long g = GCD(a, b);
  a /= g;
  b /= g;
  c /= g;
  Pair p = ExtendedEuclidean(a, b);
  p.first *= c;
  p.second *= c;
  // {x, y} = {p.first - t * b, p.second + t * a}, t integer
  return {p, {-b, a}};
}

Long Mod(__int128 a, Long m) {
  return ((a % m) + m) % m;
}

// Find x such that ax = 1 (mod m)
Long Invert(Long a, Long m) {
  assert(GCD(a, m) == 1);
  Long x = LinearDiophantine(a, m, 1LL).first.first;
  return Mod(x, m);
}

// ax = b (mod m)
Pair Solve(Trio equation) {
  Long a = get<0>(equation);
  Long b = get<1>(equation);
  Long m = get<2>(equation);
  Long g = GCD(a, m);
  if (g == 1) return {Mod(b * Invert(a, m), m), m};
  if (b % g == 0) return Solve(make_tuple(a / g, b / g, m / g));
  return {-1LL, -1LL};
}

// Find x such that a_i * x = b_i (mod m_i)
// Return {x, lcm(m_i)}
Pair CRT(vector<Trio> equations) {
  Long x = 0, lcm = 1, y, m;
  for (auto equation : equations) {
    tie(y, m) = Solve(equation);
    if ((x - y) % GCD(lcm, m) != 0) return {-1LL, -1LL};
    if (lcm == m) continue;
    Long k = LinearDiophantine(m, -lcm, x - y).first.second;
    Long n = lcm * (m / GCD(lcm, m));
    x = Mod((__int128)lcm * k + x, n);
    lcm = n;
  }
  return Solve(make_tuple(1LL, x, lcm));
}

void Go(void) {
  vector<Trio> equations;
  for (int i = 0; i < 2; i++) {
    Long a = 1LL;
    Long b, m;
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