namespace Mask {
  bool Get(Long& m, int b) { return (m >> b) & 1LL; }
  void On(Long &m, int b) { m |= (1LL << b); }
  void Off(Long& m, int b) { m &= ~(1LL << b); }
  void Set(Long& m, int b, bool v) { v ? On(m, b) : Off(m, b); }
  void Flip(Long& m, int b) { m ^= (1LL << b); }
  int Highest(unsigned m) { return m == 0 ? -1 : 31 - __builtin_clz(m); }
}