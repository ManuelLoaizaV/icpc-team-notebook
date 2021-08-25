// MAX_N must be power of 2
// MOD - 1 needs to be a multiple of MAX_N
// Big mod and primitive root for NTT
typedef Long Type;
typedef vector<Type> Poly;
const int MAX_N = (1 << 20);
const Type MOD = 998244353, ROOT = 3;
// FFT
struct Complex{
	double r, i;
	Complex(double r = 0, double i = 0): r(r), i(i) {}
	double Real(void) const { return r; }
	void operator /= (const int c) { r /= c, i /= c; }
};
Complex operator * (const Complex& a, const Complex& b) { return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
Complex operator + (const Complex& a, const Complex& b) { return Complex(a.r + b.r, a.i + b.i); }
Complex operator - (const Complex& a, const Complex& b) { return Complex(a.r - b.r, a.i - b.i); }
const double PI = acos(-1.0);
/* NTT
struct Complex {
	Type x;
	Complex(Type x): x(x) {}
	Complex() {}
};
Type Add(Type a, Type b) { a += b; if (a >= MOD) a -= MOD; return a; }
Type Sub(Type a, Type b) { a -= b; if (a < 0) a += MOD; return a; }
Type Mul(Long a, Long b) { return ((a * b) % MOD); }
Type Pow(Type base, Type exp) {
  Type result = 1;
  while (exp > 0) {
    if(exp & 1) result = Mul(result, base);
    base = Mul(base, base);
    exp >>= 1;
  }
  return result;
}
Complex operator * (const Complex& a, const Complex& b) { return Complex(Mul(a.x, b.x)); }
Complex operator + (const Complex& a, const Complex& b) { return Complex(Add(a.x, b.x)); }
Complex operator - (const Complex& a, const Complex& b) { return Complex(Sub(a.x, b.x)); }
vector<Type> rts(MAX_N + 9, -1);
Complex Root(int n, bool inv){
	Type r = (rts[n] < 0 ? rts[n] = Pow(ROOT, (MOD - 1) / n): rts[n]);
	return Complex(inv ? Pow(r, MOD - 2): r);
}
*/
Complex cp1[MAX_N + 9], cp2[MAX_N + 9];
int R[MAX_N + 9];
void DFT(Complex* a, int n, bool inv) {
	for (int i = 0; i < n; i++) if (R[i] < i) swap(a[R[i]] ,a[i]);
	for (int m = 2; m <= n; m *= 2) {
		double z = 2 * pi / m * (inv ? -1: 1); // FFT
		Complex wi = Complex(cos(z), sin(z)); // FFT
		// Complex wi = Root(m, inv); // NTT
		for (int j = 0; j < n; j += m) {
			Complex w(1);
			for (int k = j, k2 = j + m / 2; k2 < j + m; k++, k2++) {
				Complex u = a[k]; Complex v = a[k2] * w; 
        a[k] = u + v; a[k2] = u - v; 
        w = w * wi;
			}
		}
	}
	if (inv) for(int i = 0; i < n; i++) a[i] /= n; // FFT
	/*
  if (inv) { // NTT
		Complex z(Pow(n, MOD-2)); // Pow: modular exponentiation
		for (int i = 0; i < n; i++) a[i] = a[i] * z;
	}
	*/
}
Poly Multiply(Poly& p1, Poly& p2){
	int n = p1.size() + p2.size() + 1;
	int m = 1, cnt = 0;
	while (m <= n) m += m, cnt++;
	for (int i = 0; i < m; i++) {
    R[i] = 0; 
    for (int j = 0; j < cnt; j++) R[i] = (R[i] << 1) | ((i >> j) & 1);
  }
	for (int i = 0; i < m; i++) cp1[i] = 0, cp2[i] = 0;
	for (int i = 0; i < p1.size(); i++) cp1[i] = p1[i];
	for (int i = 0; i < p2.size(); i++) cp2[i] = p2[i];
	DFT(cp1, m, 0); DFT(cp2, m, 0);
	for (int i = 0; i < m; i++) cp1[i] = cp1[i] * cp2[i];
	DFT(cp1, m, 1);
	Poly result;
	n -= 2;
	for (int i = 0; i < n; i++) result.push_back((Type) floor(cp1[i].Real() + 0.5)); // FFT
	// for (int i = 0; i < n; i++) result.push_back(cp1[i].x); // NTT
	return result;
}