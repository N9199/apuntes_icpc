#include "../../headers/headers.h"

int inline op(int a, int b) { return (a + b) % 100; }
int inline cost(int a, int b) { return a * b; }

vector<vector<ll>> DP;
vector<vector<int>> A;

// Minimize on [i,j]
ll func(int i, int j)
{
    if (DP[i][j] != -1)
        return DP[i][j];
    ll temp, ans = 1e9;
    repx(k, i, j)
    {
        temp = cost(A[i][k], A[k + 1][j]) + func(i, k) + func(k + 1, j);
        ans = min(ans, temp);
    }
    return DP[i][j] = ans;
}
void inline fill() { rep(i, A.size()) repx(j, i + 1, A.size()) A[i][j] = op(A[i][j - 1], A[j][j]); }

// Call func(0, DP.size()-1)
