bool EqualSign(Long a, Long b) {
  return a > 0 && b > 0 || a < 0 && b < 0;
}
Long FloorDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (EqualSign(a, b)) return abs(a) / abs(b);
  return (-1LL) * (1LL + (abs(a) - 1) / abs(b));
}
Long CeilDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (!EqualSign(a, b)) return (-1LL) * (abs(a) / abs(b));
  return 1LL + (abs(a) - 1LL) / abs(b);
}