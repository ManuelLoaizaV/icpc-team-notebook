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