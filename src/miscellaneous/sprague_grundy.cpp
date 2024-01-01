const int N = 1e3;
bool used[N];
int dp[N];
int Mex(const vector<int>& v) {
  int n = (int)v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int x = 0; x < n; x++) if (!marked[x]) return x;
  return n;
}
// A short impartial game is a N-game iff its grundy value is positive.
// Nim sum. g(G + H) = g(G) ^ g(H).
// Sprague-Grundy. Every short impartial game is equivalent to some one-pile nim game.
int Grundy(Position p) {
  if (pos is terminal) return 0;
  if (used[p]) return dp[p];
  used[p] = true;
  vector<Position> moves = positions I can move to;
  vector<int> g;
  for (auto nxt : moves) g.push_back(Grundy(nxt));
  return dp[p] = Mex(g);
}
