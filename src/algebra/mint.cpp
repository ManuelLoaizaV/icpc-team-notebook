struct Mint {
  Long v; // Holds the value of the modular integer
  explicit operator Long() const { return v; }
  // Constructors
  Mint() { v = 0; }
  Mint(Long _v) {
    // Modulo operation to keep value in range [-MOD, MOD)
    v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
    if (v < 0) v += MOD; // Ensure non-negative value
  }
  // Comparison operators
  friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
  friend bool operator!=(const Mint &a, const Mint &b) { return !(a == b); }
  friend bool operator<(const Mint &a, const Mint &b) { return a.v < b.v; }
  // Arithmetic operators
  Mint &operator+=(const Mint &m) {
    if ((v += m.v) >= MOD) v -= MOD;
    return *this;
  }
  Mint &operator-=(const Mint &m) {
    if ((v -= m.v) < 0) v += MOD;
    return *this;
  }
  Mint &operator*=(const Mint &m) {
    v = v * m.v % MOD;
    return *this;
  }
  Mint &operator/=(const Mint &m) { return (*this) *= inv(m); }
  // Utility functions
  friend Mint pow(Mint a, Long p) {
    Mint ans = 1;
    assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
    return ans;
  }
  friend Mint inv(const Mint &a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }
  Mint operator-() const { return Mint(-v); }
  Mint &operator++() { return *this += 1; }
  Mint &operator--() { return *this -= 1; }
  Mint operator++(int) {
    v++;
    if (v == MOD) v = 0;
    return Mint(v);
  }
  Mint operator--(int) {
    v--;
    if (v < 0) v = MOD - 1;
    return Mint(v);
  }
  // Binary arithmetic operators
  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
  // Stream insertion and extraction operators
  friend ostream &operator<<(ostream &os, const Mint &m) {
    os << m.v;
    return os;
  }
  friend istream &operator>>(istream &is, Mint &m) {
    Long x;
    is >> x;
    m.v = x;
    return is;
  }
};