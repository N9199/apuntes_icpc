#include "../../headers/headers.h"

class Centroid {
  graph Tree;
  vi d;
  vi p;
  int n;

  void find_centroids(int root, int par, graph &g) {
    static vi sz(g.size());
    function<void(int, int)> get_sz = [&](int u, int prev) {
      sz[u] = 1;
      for (auto v : g[u])
        if (v != prev and p[v] == -2) {
          get_sz(v, u);
          sz[u] += sz[v];
        }
    };
    get_sz(root, -1);
    int n = sz[root];
    int centroid = -1;
    function<void(int, int)> dfs = [&](int u, int prev) {
      bool is_centroid = true;
      for (auto v : g[u])
        if (v != prev and p[v] == -2) {
          dfs(v, u);
          if (sz[v] > n / 2)
            is_centroid = false;
        }
      if (n - sz[u] > n / 2)
        is_centroid = false;
      if (is_centroid)
        centroid = u;
    };
    dfs(root, -1);
    p[centroid] = par;
    for (auto v : g[centroid])
      if (p[v] == -2)
        find_centroids(v, centroid, g);
  }

public:
  Centroid(graph &g) {
    n = g.size();
    Tree.resize(n);
    p.resize(n);
    rep(i, n) p[i] = -2;
    d.assign(n, -1);
    find_centroids(0, -1, g);
  }
  int parent(int u) { return p[u]; }
  int depth(int u) {
    return (d[u] != -1)
               ? d[u]
               : ((parent(u) == -1) ? d[u] = 0 : d[u] = depth(parent(u)) + 1);
  }
};