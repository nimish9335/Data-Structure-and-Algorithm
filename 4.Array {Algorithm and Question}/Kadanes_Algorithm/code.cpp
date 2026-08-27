#include <bits/stdc++.h>
using namespace std;

int maxSubArrayBrute(vector<int>& arr) {
    int n = arr.size();
    int maxi = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
            maxi = max(maxi, sum);
        }
    }

    return maxi;
}

int maxSubArrayBetter(vector<int>& arr) {
    int n = arr.size();
    int maxi = INT_MIN;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            maxi = max(maxi, sum);
        }
    }

    return maxi;
}

int maxSubArrayKadane(vector<int>& arr) {
    int sum = 0;
    int maxi = INT_MIN;

    for (int x : arr) {
        sum += x;
        maxi = max(maxi, sum);
        if (sum < 0) sum = 0;
    }

    return maxi;
}

vector<int> maxSubArrayWithIndices(vector<int>& arr) {
    int sum = 0;
    int maxi = INT_MIN;
    int start = 0, ansStart = 0, ansEnd = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        if (sum == 0) start = i;
        sum += arr[i];

        if (sum > maxi) {
            maxi = sum;
            ansStart = start;
            ansEnd = i;
        }

        if (sum < 0) sum = 0;
    }

    vector<int> subarray(arr.begin() + ansStart, arr.begin() + ansEnd + 1);
    return subarray;
}

int main() {
    vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "Brute Force: " << maxSubArrayBrute(arr1) << endl;
    cout << "Better: " << maxSubArrayBetter(arr1) << endl;
    cout << "Kadane's (Optimal): " << maxSubArrayKadane(arr1) << endl;

    vector<int> subarray = maxSubArrayWithIndices(arr1);
    cout << "Max Sum Subarray: ";
    for (int x : subarray) cout << x << " ";
    cout << endl;

    return 0;
}
