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