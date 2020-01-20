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

int main() {
	for (long long i = 0LL; i <= N; i++)
		cout << "2 ^ " << i << " = " << fast_pow(2LL, i, MOD) << "(mod " << MOD << ")" << endl;
	return 0;
}