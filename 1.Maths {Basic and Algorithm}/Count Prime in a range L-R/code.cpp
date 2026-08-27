#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000001;

vector<int> buildPrefixPrimeCount(int maxN) {
    vector<int> isPrime(maxN + 1, 1);
    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; (long long)i * i <= maxN; i++) {
        if (isPrime[i] == 1) {
            for (int j = i * i; j <= maxN; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    vector<int> prefix(maxN + 1, 0);
    for (int i = 1; i <= maxN; i++) {
        prefix[i] = prefix[i - 1] + isPrime[i];
    }
    return prefix;
}

int countPrimesInRange(vector<int> &prefix, int L, int R) {
    return prefix[R] - prefix[L - 1];
}

int main() {
    int maxN = MAXN - 1;
    vector<int> prefix = buildPrefixPrimeCount(maxN);

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    while (q--) {
        int L, R;
        cout << "Enter L and R: ";
        cin >> L >> R;
        cout << "Count of primes in [" << L << ", " << R << "]: "
             << countPrimesInRange(prefix, L, R) << endl;
    }

    return 0;
}
