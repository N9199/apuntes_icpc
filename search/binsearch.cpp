#include "../headers/headers.h"
// On iterables v use lower_bound(v.begin(),v.begin()+delta,key) and upper_bound(v.begin(), v.begin()+delta,key)

int val;
vi vals;
bool discreteP(int x) { return x > val; }

int bin(int start, int end)
{
    int left = start, right = end, mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (discreteP(vals[mid]))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

double approx;
bool continuousP(double x) { return x > approx; }

double bin(double start, double end)
{
    double left = start, right = end;
    int reps = 80; //Safe numbers check if viable for problem
    double mid;
    rep(_, reps)
    {
        mid = (left + right) / 2;
        if (continuousP(mid))
            right = mid;
        else
            left = mid;
    }
    return mid;
}