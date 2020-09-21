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

template <class node> class PST {
  vector<node> st;
  vector<umap<int, ii>> keys;
  // given version v and node u keys[v][u] is the pair {i, ver}, where
  // i is the index of st which corresponds to node u of version v and ver is
  // the original version of node u
  int n, k, last;

  void build(int u, int i, int j, vector<node> &arr) {
    if (u > last) {
      st.resize(u + 3);
      last = max(last, u + 1);
    }
    keys[0][u] = ii(u, 0);
    last = max(last, u);
    if (i == j) {
      st[u] = node(arr[i]);
      return;
    }
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    build(l, i, m, arr);
    build(r, m + 1, j, arr);
    st[u] = node(st[l], st[r]);
  }

  void propagate(int u, int v, int i, int j, ll x) {
    st[u] = node(i, j, x, st[u]);
    if (i != j) {
      st[u * 2 + 1] = node(x, st[u * 2 + 1]);
      st[u * 2 + 2] = node(x, st[u * 2 + 2]);
    }
  }

  node query(int a, int b, int v, int u, int i, int j) {
    if (j < a or b < i)
      return node();
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    if (st[u].lazy)
      propagate(u, v, i, j, st[u].lazy_value);
    if (a <= i and j <= b) {
      return st[u];
    }
    node x = query(a, b, v, l, i, m);
    node y = query(a, b, v, r, m + 1, j);
    return node(x, y);
  }
  // Add 20 for n<=1e6
  void update(int a, int b, int v, ll value, int u, int i, int j) {
    int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
    if (st[u].lazy)
      propagate(u, v, i, j, st[u].lazy_value);
    if (a <= i and j <= b)
      propagate(u, v, i, j, value);
    else if (j < a or b < i)
      return;
    else {
      update(a, b, v, value, l, i, m);
      update(a, b, v, value, r, m + 1, j);
      st[u] = node(st[u], st[u]);
    }
  }

public:
  PST(vector<node> &arr) {
    n = arr.size(), k = 1, last = 0;
    keys.pb();
    st.reserve(4 * n);
    build(0, 0, n - 1, arr);
  }

  node query(int a, int b, int v) { return query(a, b, v, 0, 0, n - 1); }

  void update(int a, int b, int v, ll value) {
    keys.pb();
    k++;
    update(a, b, v, value, 0, 0, n - 1);
  }
};
