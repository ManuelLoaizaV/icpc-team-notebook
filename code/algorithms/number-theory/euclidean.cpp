Long GCD(Long a, Long b) {
  if (b == 0) return abs(a);
  return GCD(b, a % b);
}
Long GCD(Long a, Long b) {
  while (b != 0) {
    a = a % b;
    swap(a, b);
  }
  return abs(a);
}
Long LCM(Long a, Long b) {
  return abs(a) / GCD(a, b) * abs(b);
}