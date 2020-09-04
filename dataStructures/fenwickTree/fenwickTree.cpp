#include "../../headers/headers.h"

struct FenwickTree {
  vector<int> FT;
  FenwickTree(int N) { FT.resize(N + 2, 0); }
  // Queries puntuales y Updates por rango
  // xor
  // Queries por rango y Updates puntuales
  int query(int i) {
    int ans = 0;
    for (; i; i -= i & (-i))
      ans += FT[i];
    return ans;
  }

  int query(int i, int j) { return query(j) - query(i - 1); }

  void update(int i, int v) {
    int s = query(i, i); // Sets range to v?
    for (; i < FT.size(); i += i & (-i))
      FT[i] += v - s;
  }

  void update(int i, int j, int v) {
    update(i, v);
    update(j + 1, -v);
  }
};