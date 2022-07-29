// https://open.kattis.com/problems/modulararithmetic
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

Long Mod(Long a, Long m) {
  Long r = a % m;
  if (r < 0) r += m;
  return r;
}

Long Add(Long a, Long b, Long m) {
  return Mod(Mod(a, m) + Mod(b, m), m);
}

Long Mul(Long a, Long b, Long m) {
  return Mod(Mod(a, m) * Mod(b, m), m);
}

Long Sub(Long a, Long b, Long m) {
  return Mod(Mod(a, m) - Mod(b, m) + m, m);
}

// Solves ax + by = gcd(a, b).
Pair Bezout(Long a, Long b) {
  if (b == 0) {
    if (a >= 0) return {1LL, 0LL};
    return {-1LL, 0LL};
  }
  Pair p = Bezout(b, a % b);
  Long x = p.second;
  Long y = p.first - (a / b) * p.second;
  return {x, y};
}

void Solve(Long n, Long t) {
  while (t--) {
    Long a, b;
    string op;
    cin >> a >> op >> b;
    Long ans = -1;
    if (op == "+") {
      ans = Add(a, b, n);
    } else if (op == "-") {
      ans = Sub(a, b, n);
    } else if (op == "*") {
      ans = Mul(a, b, n);
    } else if (op == "/") {
      if (b == 0) {
        ans = -1;
      } else {
        // bx + ny = 1
        // bx = 1 (mod n)
        Pair xy = Bezout(b, n);
        Long x = xy.first;
        Long y = xy.second;
        if (b * x + n * y != 1) {
          ans = -1;
        } else {
          ans = Mul(a, x, n);
        }
      }
    }
    cout << ans << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long n, t;
  while (cin >> n >> t) {
    if (n == 0 && t == 0) break;
    Solve(n, t);
  }
  return 0;
}