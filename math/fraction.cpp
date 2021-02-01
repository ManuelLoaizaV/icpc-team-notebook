struct Fraction {
  Long num, den;
  Fraction() {}
  Fraction(Long n, Long d) {
    if (d == 0) {
      num = INF;
      den = 1;
      if (num <= 0) num *= -1;
    } else {
      num = n;
      den = d;
      if (d < 0) {
        n *= -1;
        d *= -1;
      }
    }
  }
  void Normalize(void) {
    if (num == 0 && den == 0) return;
    Long g = __gcd(abs(num), abs(den));
    num /= g;
    den /= g;
  }
  Fraction operator + (const Fraction& f) const {
    Long g = __gcd(den, f.den);
    return Fraction(num * (f.den / g) + f.num * (den / g), den * (f.den / g));
  }
  Fraction operator - (const Fraction& f) const {
    Long g = __gcd(den, f.den);
    return Fraction(num * (f.den / g) - f.num * (den / g), den * (f. den / g));
  }
  Fraction operator * (const Fraction& f) const {
    return Fraction(num * f.num, den * f.den);
  }
  Fraction operator / (const Fraction& f) const {
    return Fraction(num * f.den, den * f.num);
  }
  bool operator == (const Fraction& f) const {
    return num * f.den == f.num * den;
  }
  bool operator != (const Fraction& f) const {
    return !(*this == f);
  }
  bool operator < (const Fraction& f) const {
    return num * f.den < f.num * den;
  }
  bool operator > (const Fraction& f) const {
    return num * f.den > f.num * den;
  }
  bool operator <= (const Fraction& f) const {
    return *this < f || *this == f;
  }
  bool operator >= (const Fraction& f) const {
    return *this > f || *this == f;
  }
  Double GetValue(void) { return (Double) num / den; }
};
ostream& operator << (ostream& s, const Fraction& f) {
  s << f.num << " / " << f.den;
  return s;
}
