#include "../../headers/headers.h"

// ----------------------------------------------
// Convex Hull: Andrew's Montone Chain Algorithm
// ----------------------------------------------
struct Point {
  ll x, y;
  bool operator<(const Point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};

ll cross(Point &a, Point &b, Point &c) {
  ll dx0 = b.x - a.x, dy0 = b.y - a.y;
  ll dx1 = c.x - a.x, dy1 = c.y - a.y;
  return dx0 * dy1 - dx1 * dy0;
}

vector<Point> upper_hull(vector<Point> &P) {
  // sort points lexicographically
  int n = P.size(), k = 0;
  sort(P.begin(), P.end());
  // build upper hull
  vector<Point> uh(n);
  invrep(i, n, 0) {
    while (k >= 2 && cross(uh[k - 2], uh[k - 1], P[i]) <= 0)
      k--;
    uh[k++] = P[i];
  }
  uh.resize(k);
  return uh;
}

vector<Point> lower_hull(vector<Point> &P) {
  // sort points lexicographically
  int n = P.size(), k = 0;
  sort(P.begin(), P.end());
  // collect lower hull
  vector<Point> lh(n);
  rep(i, n) {
    while (k >= 2 && cross(lh[k - 2], lh[k - 1], P[i]) <= 0)
      k--;
    lh[k++] = P[i];
  }
  lh.resize(k);
  return lh;
}

vector<Point> convex_hull(vector<Point> &P) {
  int n = P.size(), k = 0;
  // set initial capacity
  vector<Point> H(2 * n);
  // sort points lexicographically
  sort(P.begin(), P.end());
  // build lower hull
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }
  // build upper hull
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)
      k--;
    H[k++] = P[i];
  }
  // remove extra space
  H.resize(k - 1);
  return H;
}