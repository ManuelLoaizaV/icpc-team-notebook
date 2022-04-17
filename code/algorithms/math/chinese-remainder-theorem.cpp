Long Mod(__int128 a, Long m) { return ((a % m) + m) % m; }
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
  if (g == 1) return {Mod((__int128)b * Invert(a, m), m), m};
  if (b % g == 0) return Solve(make_tuple(a / g, b / g, m / g));
  return {-1LL, -1LL};
}
// Find x such that a_i * x = b_i (mod m_i)
// Return {x, lcm(m_i)}
Pair CRT(vector<Trio> equations) {
  Long b = 0LL, lcm = 1LL, y, m;
  for (auto equation : equations) {
    tie(y, m) = Solve(equation);  // a_i * y = b_i (mod m)
    if ((b - y) % GCD(lcm, m) != 0) return {-1LL, -1LL};
    if (lcm == m) continue;
    Long k = LinearDiophantine(m, -lcm, b - y).first.second;
    Long new_lcm = lcm * (m / GCD(lcm, m));
    b = Mod((__int128)lcm * k + b, new_lcm);
    lcm = new_lcm;
  }
  return Solve(make_tuple(1LL, b, lcm));
}