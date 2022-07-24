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