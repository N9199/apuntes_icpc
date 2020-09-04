#include "../../headers/headers.h"

vi L;
vi A;
int curr_l = 1;

// Bottom up approach O(nlogn)
int lis(int n) {
  L.assign(n, -1);
  L[0] = A[0];
  repx(i, 1, n) {
    auto it = lower_bound(L.begin(), L.begin() + curr_l, A[i]);
    if (it == L.begin() + curr_l) {
      L[curr_l] = A[i];
      curr_l++;
    } else
      *it = A[i];
  }
  return curr_l;
}