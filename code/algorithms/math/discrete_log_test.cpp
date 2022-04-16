#include <bits/stdc++.h>
using namespace std;

const long long N = 50;
const long long MOD = 1e9 + 7;

long long fast_pow(long long a, long long b, long long m) {
	long long ans = 1LL;
	while (b > 0) {
		if (b & 1) ans = (ans * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return ans;
}

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

int main() {
	cout << "2^x = 1024 (mod 10^9 + 7), x = " << discrete_log(2, 1024, MOD) << endl;
	cout << "2^x = 0 (mod 10^9 + 7), x = " << discrete_log(2, 0, MOD) << endl;
	cout << "3^x = 1 (mod 10^9 + 7), x = " << discrete_log(3, 1, MOD) << endl;
	cout << "3^x = 2 (mod 5), x = " << discrete_log(3, 2, 5) << endl;
	cout << "3^x = 5 (mod 8), x = " << discrete_log(3, 5, 8) << endl;
	cout << "5^x = 9 (mod 16), x = " << discrete_log(5, 9, 16) << endl;
	return 0;
}