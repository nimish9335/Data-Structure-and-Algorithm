#include <bits/stdc++.h>
using namespace std;

class SqrtDecomposition {
    vector<long long> arr;
    vector<long long> block;
    int n, blockSize, numBlocks;

public:
    SqrtDecomposition(vector<long long>& input) {
        n = input.size();
        arr = input;
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        block.assign(numBlocks, 0);

        for (int i = 0; i < n; i++) {
            block[i / blockSize] += arr[i];
        }
    }

    void update(int i, long long val) {
        int b = i / blockSize;
        block[b] += val - arr[i];
        arr[i] = val;
    }

    long long query(int l, int r) {
        long long sum = 0;
        while (l <= r) {
            if (l % blockSize == 0 && l + blockSize - 1 <= r) {
                sum += block[l / blockSize];
                l += blockSize;
            } else {
                sum += arr[l];
                l++;
            }
        }
        return sum;
    }
};

int main() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (auto& x : arr) cin >> x;

    SqrtDecomposition sd(arr);

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i; long long val;
            cin >> i >> val;
            sd.update(i, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sd.query(l, r) << "\n";
        }
    }
    return 0;
}
