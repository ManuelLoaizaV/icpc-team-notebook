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