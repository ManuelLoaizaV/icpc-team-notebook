long long fast_pow(long long a, long long b, long long m) {
	long long ans = 1LL;
	while (b > 0) {
		if (b & 1) ans = (ans * a) % m;
		a = (a * a) % m;
		b >= 1;
	}
	return ans;
}