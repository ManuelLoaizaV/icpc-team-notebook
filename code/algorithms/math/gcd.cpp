Long GCD(Long a, Long b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}