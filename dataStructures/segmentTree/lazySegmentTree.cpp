#include "../../headers/headers.h"

// Range Sum Query where update sets
struct rsum {
  ll value;
  ll lazy_value = 0;
  bool lazy = false;
  rsum() { value = 0; } // identity
  rsum(ll x) { value = x; }
  rsum(const rsum &a, const rsum &b) { value = a.value + b.value; } // op
  rsum(int i, int j, int x, const rsum &b) {                        // lazy op
    value = x * (j - i + 1);
  }
  rsum(int x, const rsum &b) { // lazy update
    value = b.value, lazy = true, lazy_value = x;
  }
};

// Range Min Query where update sums
struct rminq {
  ll value;
  ll lazy_value = 0;
  bool lazy = false;
  rminq() { value = 1e18; } // identity
  rminq(ll x) { value = x; }
  rminq(const rminq &a, const rminq &b) { value = min(a.value, b.value); } // op
  rminq(int i, int j, int x, const rminq &b) { value = x + b.value; } // lazy op
  rminq(int x, const rminq &b) { // lazy update
    value = b.value, lazy = true, lazy_value = x + b.lazy_value;
  }
};

template <class node> class STL {
  vector<node> st;
  int n;

  void build(int u, int i, int j, vector<node> &arr) {
    if (i == j) {
      st[u] = node(arr[i]);
      return;
    }
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    build(l, i, m, arr);
    build(r, m + 1, j, arr);
    st[u] = node(st[l], st[r]);
  }

  void propagate(int u, int i, int j, ll x) {
    st[u] = node(i, j, x, st[u]);
    if (i != j) {
      st[u * 2 + 1] = node(x, st[u * 2 + 1]);
      st[u * 2 + 2] = node(x, st[u * 2 + 2]);
    }
  }

  node query(int a, int b, int u, int i, int j) {
    if (j < a or b < i)
      return node();
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    if (st[u].lazy)
      propagate(u, i, j, st[u].lazy_value);
    if (a <= i and j <= b) {
      return st[u];
    }
    node x = query(a, b, l, i, m);
    node y = query(a, b, r, m + 1, j);
    return node(x, y);
  }

  void update(int a, int b, ll value, int u, int i, int j) {
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    if (st[u].lazy)
      propagate(u, i, j, st[u].lazy_value);
    if (a <= i and j <= b)
      propagate(u, i, j, value);
    else if (j < a or b < i)
      return;
    else {
      update(a, b, value, l, i, m);
      update(a, b, value, r, m + 1, j);
      st[u] = node(st[l], st[r]);
    }
  }

public:
  STL(vector<node> &v) {
    n = v.size();
    st.resize(n * 4 + 5);
    build(0, 0, n - 1, v);
  }

  node query(int a, int b) { return query(a, b, 0, 0, n - 1); }

  void update(int a, int b, ll value) { update(a, b, value, 0, 0, n - 1); }
};
