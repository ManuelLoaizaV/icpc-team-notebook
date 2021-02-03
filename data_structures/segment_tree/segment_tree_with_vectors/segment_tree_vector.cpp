const int N = 1e5, INF = 1e9;
struct SegmentTree {
    vector<int> t[4 * N];//O(nlgn)
    //O(n)
    vector<int> combine(vector<int> &L, vector<int> &R) {
        int pos_L = 0;
        int pos_R = 0;
        vector<int> ans;
        int sz = L.size() + R.size();
        for (int i = 0; i < sz; i++) {
            if (pos_L == L.size()) {
                ans.push_back(R[pos_R]);
                pos_R++;
            } else {
                if (pos_R == R.size()) {
                    ans.push_back(L[pos_L]);
                    pos_L++;
                } else {
                    if (L[pos_L] < R[pos_R]) {
                        ans.push_back(L[pos_L]);
                        pos_L++;
                    } else {
                        ans.push_back(R[pos_R]);
                        pos_R++;
                    }
                }
            }
        }
        return ans;
    }
    int combine(int x, int y) {
        return min(x, y);
    }
    //O(nlgn)
    void build(vector<int> &a, int id, int tl, int tr) {
        if (tl == tr) {
            t[id] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            //int left = id + 1;
            //int right = id + 2 * (tm - tl + 1);
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            t[id] = combine(t[2 * id], t[2 * id + 1]);
            //merge(t[left].begin(), t[left].end(), t[right].begin(), t[right].end(), back_inserter(t[id]));
        }
    }
    // O(n), si no hay updates, usar vectos basta. Con updates usar multiset u ost
    void update(int pos, int val, int id, int tl, int tr) {
        if (tl == tr) {
            t[id] = {val};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(pos, val, 2 * id, tl, tm);
            else update(pos, val, 2 * id + 1, tm + 1, tr);
            t[id] = combine(t[2 * id], t[2 * id + 1]);
        }
    }
    //O(lg^2(n))
    int query(int l, int r, int x, int id, int tl, int tr) {
        if (l <= tl and tr <= r) {
            auto it = lower_bound(t[id].begin(), t[id].end(), x);
            if (it == t[id].end()) return INF;
            else return *it;
        }
        int tm = (tl + tr) / 2;
        if (r <= tm) return query(l, r, x, 2 * id, tl, tm);
        if (tm < l) return query(l, r, x, 2 * id + 1, tm + 1, tr);
        return combine(query(l, r, x, 2 * id, tl, tm), query(l, r, x, 2 * id + 1, tm + 1, tr));
    }
} st;