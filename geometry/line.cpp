int sgn2(long double x) { return x < 0 ? -1 : 1; }
struct Line {
	Punto p, pq;
	Line() {}
	Line(Punto x, Punto y) { p = x; pq = y - x; }
	bool has(Punto r) { return dist(r) <= EPS; }
	bool seghas(Punto r) { return has(r) and (r - p) * (r - (p + pq)) <= EPS; }
	// Chequea si dos rectas son paralelas
	bool operator / (Line l) { return abs(pq.unit() % l.pq.unit()) <= EPS; } // 2D
//	bool operator / (Line l) { return (pq.unit() ^ l.pq.unit()).norm() <= EPS; } // 3D
	bool operator == (Line l) { return *this / l and has(l.p); }
	// Interseccion entre dos rectas
	Punto operator ^ (Line l) {
		if (*this / l) return Punto(DINF, DINF);
		Punto i = l.p + l.pq * (((p - l.p) % pq) / (l.pq % pq));
//		if (not has(i)) return Punto(NAN, NAN, NAN); // 3D
		return i;
	}
	long double angle(Line l) { return pq.angle(l.pq); }
	int side(Punto r) { return has(r) ? 0 : sgn2(pq % (r - p)); } // 2D
	Punto proy(Punto r) { return p + pq * ((r - p) * pq) / pq.norm2(); }
	Punto ref(Punto r) { return proy(r) * 2 - r; }
	long double dist(Punto r) { (r - proy(r)).norm(); }
	// Distancia entre dos rectas 3D
//	long double dist(Line l) {
//		if (*this / l) return dist(l.p);
//		return abs((l.p - p) * (pq ^ l.pq)) / (pq ^ l.pq).norm();
//	}
	Line rot(Punto r) { return Line(p, p + pq.rot(r)); }
};
// Recta bisectriz
Line bisector(Line a, Line b) {
	Punto p = a ^ b;
	return Line(p, p + a.pq.unit() + b.pq.unit());
}
// Recta mediatriz de un segmento
Line bisector(Punto l, Punto r) {
	Punto mid = (l + r) / 2;
	return Line(mid, l).rot(ccw90);
}