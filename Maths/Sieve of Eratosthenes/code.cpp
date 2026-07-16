#include <bits/stdc++.h>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<int> isPrime(n + 1, 1);
    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; (long long)i * i <= n; i++) {
        if (isPrime[i] == 1) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i] == 1) {
            primes.push_back(i);
        }
    }
    return primes;
}

