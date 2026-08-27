#include <bits/stdc++.h>
using namespace std;

// ================= Prime Check Helper =================
bool isPrimeHelper(int n) {
    if (n <= 1) return false;
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i != n / i) cnt++;
        }
    }
    return cnt == 2;
}

// ================= Naive Approach =================
void primeFactorsNaive(int n) {
    for (int i = 2; i <= n; i++) {
        if (n % i == 0 && isPrimeHelper(i)) {
            cout << i << " ";
        }
    }
}

// ================= Optimized Approach (Square Root) =================
void primeFactorsSqrt(int n) {
    vector<int> factors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (isPrimeHelper(i)) factors.push_back(i);
            int other = n / i;
            if (other != i && isPrimeHelper(other)) factors.push_back(other);
        }
    }
    sort(factors.begin(), factors.end());
    for (int f : factors) cout << f << " ";
}

// ================= School-Method Optimization =================
void primeFactorsSchoolMethod(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }
    if (n != 1) {
        factors.push_back(n);
    }
    for (int f : factors) cout << f << " ";
}
