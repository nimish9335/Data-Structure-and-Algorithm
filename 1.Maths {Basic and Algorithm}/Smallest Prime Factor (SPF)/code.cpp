#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000001;

vector<int> buildSPF(int maxN) {
    vector<int> spf(maxN + 1);
    for (int i = 0; i <= maxN; i++) {
        spf[i] = i;
    }

    for (int i = 2; (long long)i * i <= maxN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= maxN; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    return spf;
}

vector<int> getPrimeFactors(int n, vector<int> &spf) {
    vector<int> factors;
    while (n != 1) {
        factors.push_back(spf[n]);
        n = n / spf[n];
    }
    return factors;
}

int main() {
    int maxN = MAXN - 1;
    vector<int> spf = buildSPF(maxN);

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    while (q--) {
        int n;
        cout << "Enter number: ";
        cin >> n;

        vector<int> factors = getPrimeFactors(n, spf);

        cout << "Prime factorization of " << n << ": ";
        for (int f : factors) {
            cout << f << " ";
        }
        cout << endl;
    }

    return 0;
}
