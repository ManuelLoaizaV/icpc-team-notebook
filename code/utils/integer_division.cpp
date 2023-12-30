namespace Div {
  bool SameSign(Long a, Long b) {
    return a > 0 && b > 0 || a < 0 && b < 0;
  }
  Long Floor(Long a, Long b) {
    assert(b != 0);
    if (a == 0) return 0;
    if (a % b == 0) return a / b;
    if (SameSign(a, b)) return abs(a) / abs(b);
    return -((abs(a) - 1LL) / abs(b) + 1LL);
  }
  Long Ceil(Long a, Long b) {
    assert(b != 0);
    if (a == 0) return 0;
    if (a % b == 0) return a / b;
    if (!SameSign(a, b)) return (-1LL) * (abs(a) / abs(b));
    return (abs(a) - 1LL) / abs(b) + 1LL;
  }
}