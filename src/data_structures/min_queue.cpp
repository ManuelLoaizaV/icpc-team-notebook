struct MinQueue {
  stack<pair<Long, Long>> s, t;
  Long f(Long a, Long b) { return min(a, b); }
  void Push(Long e) {
    Long mn = s.empty() ? e : f(e, s.top().second);
    s.push(make_pair(e, mn));
  }
  Long Pop(void) {
    if (t.empty()) {
      while (!s.empty()) {
        Long e = s.top().first;
        s.pop();
        Long mn = t.empty() ? e : f(e, t.top().second);
        t.push(make_pair(e, mn));
      }
    }
    Long r = t.top().first;
    t.pop();
    return r;
  }
  Long Min(void) {
    if (s.empty()) return t.top().second;
    else if (t.empty()) return s.top().second;
    return f(s.top().second, t.top().second);
  }
  int Size(void) { return s.size() + t.size(); }
  void Clear(void) {
    s = stack<pair<Long, Long>>();
    t = stack<pair<Long, Long>>();
  }
};