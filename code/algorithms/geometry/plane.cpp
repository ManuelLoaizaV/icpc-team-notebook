struct Plane {
	Punto p, n; // n: vector normal unitario al plano
	Plane() {}
	Plane(Punto a, Punto b, Punto c) {
		p = a;
		n = ((b - a) ^ (c - a)).unit();
	}
	bool has(Punto q) { return abs((q - p) * n) <= EPS; }
	long double angle(Plane w) { return acos(n * w.n); }
	long double dist(Punto q) { return abs((q - p) * n); }
	Punto proy(Punto q) { inter(Line(q, q + n), q); return q; }
	bool inter(Line l, Punto &r) {
		long double x = n * (l.p + l.pq - p);
		long double y = n * (l.p - p);
		if (abs(x - y) <= EPS) return false;
		r = (l.p * x - (l.p + l.pq) * y) / (x - y);
		return true;
	}
	bool inter(Plane w, Line &l) {
		Punto nn = n ^ w.n;
		Punto q = n ^ nn;
		long double d = w.n * q;
		if (abs(d) <= EPS) return false;
		Punto r = p + q * (w.n * (w.p - p) / d);
		l = Line(r, r + nn);
		return true;
	}
};