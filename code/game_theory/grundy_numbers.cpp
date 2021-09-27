const int N = 1e3;
bool is_used[N];
int dp[N];
int Mex(const vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int x = 0; x < n; x++) if (!marked[x]) return x;
  return n;
}
// A short impartial game is a N-game iff its grundy value is positive.
// Nim sum. g(G + H) = g(G) ^ g(H).
// Sprague-Grundy. Every short impartial game is equivalent to some one-pile nim game.
int Grundy(Position pos) {
  if (pos is terminal) return 0;
  if (is_used[pos]) return dp[pos];
  is_used[pos] = true;
  vector<Position> moves = positiona I can move to;
  vector<int> g;
  for (auto next_pos : moves) g.push_back(Grundy(next_pos));
  return dp[pos] = Mex(g);
}
