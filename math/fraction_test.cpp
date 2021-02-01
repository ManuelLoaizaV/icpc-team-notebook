//A. Average Problem
//https://redprogramacioncompetitiva.com/contests/2021/01/team/problem.php
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;
typedef long double Double;

const Long INF = 1e9;

struct Fraction {
  Long num, den;
  Fraction(void) {}
  Fraction(Long n, Long d) {
    if (d == 0) {
      num = INF;
      den = 1;
      if (num <= 0) num *= -1;
    } else {
      num = n;
      den = d;
      if (d < 0) {
        n *= -1;
        d *= -1;
      }
    }
  }
  void Normalize(void) {
    if (num == 0 && den == 0) return;
    Long g = __gcd(abs(num), abs(den));
    num /= g;
    den /= g;
  }
  Fraction operator + (const Fraction& f) const {
    Long g = __gcd(den, f.den);
    return Fraction(num * (f.den / g) + f.num * (den / g), den * (f.den / g));
  }
  Fraction operator - (const Fraction& f) const {
    Long g = __gcd(den, f.den);
    return Fraction(num * (f.den / g) - f.num * (den / g), den * (f. den / g));
  }
  Fraction operator * (const Fraction& f) const {
    return Fraction(num * f.num, den * f.den);
  }
  Fraction operator / (const Fraction& f) const {
    return Fraction(num * f.den, den * f.num);
  }
  bool operator == (const Fraction& f) const {
    return num * f.den == f.num * den;
  }
  bool operator != (const Fraction& f) const {
    return !(*this == f);
  }
  bool operator < (const Fraction& f) const {
    return num * f.den < f.num * den;
  }
  bool operator > (const Fraction& f) const {
    return num * f.den > f.num * den;
  }
  bool operator <= (const Fraction& f) const {
    return *this < f || *this == f;
  }
  bool operator >= (const Fraction& f) const {
    return *this > f || *this == f;
  }
  Long GetInteger(void) { return num / den; }
  Double GetDouble(void) { return (Double) num / den; }
};
Fraction abs(const Fraction& f) {
  Fraction ans = f;
  if (ans.num < 0) ans.num *= -1;
  return ans;
}
Fraction max(const Fraction& a, const Fraction& b) {
  return (a > b) ? a : b;
}
Fraction min(const Fraction& a, const Fraction& b) {
  return (a < b) ? a : b;
}
ostream& operator << (ostream& s, const Fraction& f) {
  s << f.num << " / " << f.den;
  return s;
}


void Solve(void) {
  Long a, s;
  cin >> a >> s;
  vector<Long> evaluations(a);
  Long total = 0;
  for (int i = 0; i < a; i++) {
    cin >> evaluations[i];
    total += evaluations[i];
  }
  for (int i = 0; i < s; i++) {
    Long points = 0;
    for (int j = 0; j < a; j++) {
      Long p;
      cin >> p;
      points += p * evaluations[j];
    }
    Fraction grade(points, total);
    Long low = grade.GetInteger();
    low -= (low % 5);
    Fraction candidates[3];
    for (int i = 0; i < 3; i++) candidates[i] = Fraction(low + i * 5, 1);
    Fraction minimum = grade - candidates[0];
    for (int i = 1; i < 3; i++) {
      Fraction current = abs(grade - candidates[i]);
      minimum = min(minimum, current);
    }
    Fraction final_grade;
    for (int i = 0; i < 3; i++) {
      Fraction current = abs(grade - candidates[i]);
      if (current == minimum) {
        final_grade = candidates[i];
        break;
      }
    }
    cout << final_grade.GetInteger() << " ";
    if (final_grade < grade) {
      cout << "DOWN" << '\n';
    } else if (final_grade > grade) {
      cout << "UP" << '\n';
    } else {
      cout << "SAME" << '\n';
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    Solve();
    cout << '\n';
  }
  return 0;
}
