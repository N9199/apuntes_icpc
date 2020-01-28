#include "../../headers/headers.h"

/*
Floyd Warshall implemenation, note that g is using an adjacency matrix and not
an adjacency list
*/
static const int INF = 1e9;
graph floydWarshall(const graph g) {
  int n = g.size();
  graph dist(n, vi(n, -1));

  rep(i, n) rep(j, n) dist[i][j] = g[i][j];

  rep(k, n) rep(i, n) rep(j, n) if (dist[i][k] + dist[k][j] < dist[i][j] &&
                                    dist[i][k] != INF && dist[k][j] != INF)
      dist[i][j] = dist[i][k] + dist[k][j];

  return dist;
}
