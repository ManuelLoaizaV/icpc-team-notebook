#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  OST x;
  x.insert(1);
  x.insert(2);
  x.insert(4);
  x.insert(8);
  x.insert(16);
  cout << *x.find_by_order(1) << endl;  // 2
  cout << *x.find_by_order(2) << endl;  // 4
  cout << *x.find_by_order(4) << endl;  // 10
  cout << (end(x) == x.find_by_order(6)) << endl;  // true
  cout << x.order_of_key(-5) << endl;  // 0
  cout << x.order_of_key(1) << endl;  // 0
  cout << x.order_of_key(3) << endl;  // 2
  cout << x.order_of_key(4) << endl;  // 2
  cout << x.order_of_key(400) << endl;  // 5
  return 0;
}
