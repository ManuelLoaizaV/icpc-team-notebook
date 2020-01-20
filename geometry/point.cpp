struct Punto {
	// Para geometría 3D, añadir coordenada z, descomentar el producto cruz y comentar funciones 2D
	long double x, y;
	Punto() {}
	Punto(long double _x, long double _y) { x = _x; y = _y; }
	long double norm() { return sqrt(norm2()); }
	long double norm2() { return *this * *this; }
	bool operator == (Punto p) { return abs(x - p.x) <= EPS and abs(y - p.y) <= EPS; }
	bool operator != (Punto p) { return !(a == b); }
	Punto operator + (Punto p) { return Punto(x + p.x, y + p.y); }
	Punto operator - (Punto p) { return Punto(x - p.x, y - p.y); }
	Punto operator * (long double k) { return Punto(x * k, y * k); }
	Punto operator / (long double k) { return Punto(x / k, y / k); }
	long double operator * (Punto p) { return x * p.x + y * p.y; }
	//Punto operator ^ (Punto p) { return Punto(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
	long double angle(Punto p) { return acos(*this * p / (norm() * p.norm())); }
	Punto unit() { return *this / norm(); }
	long double operator % (Punto p) { return x * p.y - y * p.x; }
	// Lo siguiente solo funciona para geometria 2D
	bool operator < (Punto p) const { return  x < p.x - EPS or (abs(x - p.x) <= EPS and y < p.y - EPS);}
	// El punto actual se encuentra a la izquierda del vector pq
	bool left(Punto p, Punto q) { return (q - p) % (*this - p) > EPS;}
	Punto rot(Punto r) { return Punto(*this % r, *this * r); }
	Punto rot(long double x) { return rot(Punto(sin(x), cos(x))); }
};
Punto ccw90(1, 0);
Punto cw90(-1, 0);