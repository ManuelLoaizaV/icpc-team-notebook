// Hallar el menor x tal que a ^ x = b (mod m) o -1 si no existe
long long discrete_log(long long a, long long b, long long m) {
	a %= m;
	b %= m;
	if (b == 1) return 0;
	int cnt = 0;
	int temp = 1;
	for (int g = __gcd (a, m); g != 1; g = __gcd(a, m)) {
		if (b % g) return -1;
		m /= g;
		b /= g;
		temp = temp * a / g % m;
		cnt++;
		if (b == temp) return cnt;
	}
	map<long long, int> val;
	int s = ceil(sqrt(m));
	long long base = b;
	for (int i = 0; i < s; i++) {
		val[base] = i;
		base = base * a % m;
	}
	base = fast_pow(a, s, m);
	long long key = temp;
	for (int i = 1; i < s + 2; i++) {
		key = base * key % m;
		if (val.count(key)) return i * s - val[key]+ cnt;
	}
	return -1;
}