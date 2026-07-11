#include <bits/stdc++.h>
using namespace std;

long long xorUpto(long long n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}

long long rangeXor(long long l, long long r) {
    return xorUpto(r) ^ xorUpto(l - 1);
}

int main() {
    long long l, r;
    cin >> l >> r;

    cout << rangeXor(l, r);

    return 0;
}