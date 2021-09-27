// Recursive implementation
int gcd_1(int a, int b) {
	if (b == 0) return a;
	return gcd_1(b, a % b);
}

// Iterative implementation
int gcd_2(int a, int b) {
	while (b != 0) {
		a = a % b;
		swap(a, b);	
	}
	return a;
}

// a * b = lcm(a, b) * gcd(a, b)
int lcm(int a, int b) {
	return a / gcd_1(a, b) * b;
}

// a * x + b * y = gcd(a, b)
int extended_gcd(int a, int b, int *x, int *y) {
	if (b == 0) {
		(*x) = 1;
		(*y) = 0; 
		return a;
	}
	int x1, y1;
	int g = extended_gcd(b, a % b, &x1, &y1);
	(*x) = y1;
	(*y) = x1 - y1 * (a / b);
	return g;
}