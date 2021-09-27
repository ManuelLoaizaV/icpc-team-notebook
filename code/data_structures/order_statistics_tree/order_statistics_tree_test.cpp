//https://www.spoj.com/problems/ORDERS/en/
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  OST ost;
  vector<int> ans;
  for (int i = 1; i <= n; i++) ost.insert(-i);
  for (int i = n - 1; i >= 0; i--) {
    auto it = ost.find_by_order(a[i]);
    int val = (-1) * (*it);
    ans.push_back(val);
    ost.erase(it);
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
