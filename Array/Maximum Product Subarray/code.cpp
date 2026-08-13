#include <bits/stdc++.h>
using namespace std;

long long maxProductBrute(vector<int>& arr) {
    int n = arr.size();
    long long result = LLONG_MIN;

    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            result = max(result, product);
        }
    }

    return result;
}

long long maxProductOptimal1(vector<int>& arr) {
    int n = arr.size();
    long long maxProd = arr[0];
    long long minProd = arr[0];
    long long result = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            swap(maxProd, minProd);
        }

        maxProd = max((long long)arr[i], maxProd * arr[i]);
        minProd = min((long long)arr[i], minProd * arr[i]);

        result = max(result, maxProd);
    }

    return result;
}

long long maxProductOptimal2(vector<int>& arr) {
    int n = arr.size();
    long long prefix = 1, suffix = 1;
    long long result = LLONG_MIN;

    for (int i = 0; i < n; i++) {
        if (prefix == 0) prefix = 1;
        if (suffix == 0) suffix = 1;

        prefix *= arr[i];
        suffix *= arr[n - 1 - i];

        result = max({result, prefix, suffix});
    }

    return result;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5, 0};
    cout << "Brute Force: " << maxProductBrute(arr1) << endl;
    cout << "Optimal 1 (Max/Min Track): " << maxProductOptimal1(arr1) << endl;
    cout << "Optimal 2 (Prefix/Suffix): " << maxProductOptimal2(arr1) << endl;

    vector<int> arr2 = {1, 2, -3, 0, -4, -5};
    cout << "\nBrute Force: " << maxProductBrute(arr2) << endl;
    cout << "Optimal 1 (Max/Min Track): " << maxProductOptimal1(arr2) << endl;
    cout << "Optimal 2 (Prefix/Suffix): " << maxProductOptimal2(arr2) << endl;

    return 0;
}
