#include <bits/stdc++.h>
using namespace std;

// ================= Naive Approach =================
double powNaive(double x, int n) {
    double ans = 1.0;
    int absN = abs(n);
    for (int i = 1; i <= absN; i++) {
        ans = ans * x;
    }
    if (n < 0) ans = 1.0 / ans;
    return ans;
}

// ================= Optimal Approach (Binary Exponentiation) =================
double powOptimal(double x, int n) {
    double ans = 1.0;
    long long nn = n;
    if (nn < 0) nn = -1 * nn;

    while (nn > 0) {
        if (nn % 2 == 1) {
            ans = ans * x;
            nn = nn - 1;
        } else {
            x = x * x;
            nn = nn / 2;
        }
    }

    if (n < 0) ans = 1.0 / ans;
    return ans;
}
