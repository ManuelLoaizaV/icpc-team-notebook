#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

Long GCD(Long a, Long b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

void Solve(void) {
  Long a, b;
  cin >> a >> b;
  Long gcd = GCD(a, b);
  Long lcm = a / gcd * b;
  cout << gcd << " " << lcm << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}