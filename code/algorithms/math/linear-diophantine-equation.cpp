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
  // Solutions: {x, y} = {p.first - t * b, p.second + t * a}
  return {p, {-b, a}};
}