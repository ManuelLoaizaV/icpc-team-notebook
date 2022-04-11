struct Punto {
  // Para geometría 3D, añadir coordenada z, descomentar el producto cruz y comentar funciones 2D
  Double x, y;
  Punto(void) {}
  Punto(Double x, Double y) : x(x), y(y) {}
  Double Norm2() { return *this * *this; }
  Double Norm() { return sqrt(Norm2()); }
  bool operator == (const Punto& p) { return abs(x - p.x) <= EPS && abs(y - p.y) <= EPS; }
  bool operator != (const Punto& p) { return !(*this == p); }
  Punto operator + (const Punto& p) { return Punto(x + p.x, y + p.y); }
  Punto operator - (const Punto& p) { return Punto(x - p.x, y - p.y); }
  Punto operator * (Double k) { return Punto(x * k, y * k); }
  Punto operator / (Double k) { return Punto(x / k, y / k); }
  // Producto interno euclideano
  Double operator * (Punto p) { return x * p.x + y * p.y; }
//  Punto operator ^ (Punto p) { return Punto(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
  Double Angle(Punto p) { return acos(*this * p / (Norm() * p.Norm())); }
  Punto Unit(void) { return *this / Norm(); }
  // a % b = det(a | b)
  Double operator % (Punto p) { return x * p.y - y * p.x; }
  // Lo siguiente solo funciona en geometria 2D
  bool operator < (Punto p) const { return  x < p.x - EPS || (abs(x - p.x) <= EPS && y < p.y - EPS);}
  // El punto actual se encuentra a la izquierda del vector pq
  bool IsLeft(Punto p, Punto q) { return (q - p) % (*this - p) > EPS;}
  Punto Rot(Punto r) { return Punto(*this % r, *this * r); }
  Punto Rot(Double x) { return Rot(Punto(sin(x), cos(x))); }
};
const Punto CCW90(1, 0);
const Punto CW90(-1, 0);
