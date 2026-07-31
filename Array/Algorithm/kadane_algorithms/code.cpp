#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// 1. Standard Kadane's Algorithm
// Maximum Sum Subarray (Length >= 1)
//////////////////////////////////////////////////////////////////

int kadane(vector<int>& arr) {
    int currentSum = arr[0];
    int maximumSum = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        currentSum = max(arr[i], currentSum + arr[i]);
        maximumSum = max(maximumSum, currentSum);
    }

    return maximumSum;
}

//////////////////////////////////////////////////////////////////
// 2. Kadane for All Negative Arrays
// (Another Common Implementation)
// Maximum Sum Subarray (Length >= 1)
//////////////////////////////////////////////////////////////////

int kadaneAllNegative(vector<int>& arr) {
    int currentSum = 0;
    int maximumSum = INT_MIN;

    for (int x : arr) {
        currentSum += x;
        maximumSum = max(maximumSum, currentSum);

        if (currentSum < 0)
            currentSum = 0;
    }

    return maximumSum;
}

//////////////////////////////////////////////////////////////////
// 3. Modified Kadane
// Maximum Sum Subarray (Length >= 2)
//////////////////////////////////////////////////////////////////

int kadaneLengthAtLeastTwo(vector<int>& arr) {
    int n = arr.size();

    if (n < 2)
        return INT_MIN;

    int end1 = arr[0];
    int end2 = arr[0] + arr[1];

    int answer = end2;

    end1 = max(arr[1], arr[0] + arr[1]);

    for (int i = 2; i < n; i++) {

        int previousEnd1 = end1;

        // Length >= 1
        end1 = max(arr[i], end1 + arr[i]);

        // Length >= 2
        end2 = max(
            end2 + arr[i],
            previousEnd1 + arr[i]
        );

        answer = max(answer, end2);
    }

    return answer;
}

//////////////////////////////////////////////////////////////////
// Driver
//////////////////////////////////////////////////////////////////

int main() {

    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "Standard Kadane : "
         << kadane(arr) << endl;

    cout << "Kadane (Negative Supported) : "
         << kadaneAllNegative(arr) << endl;

    cout << "Length >= 2 Kadane : "
         << kadaneLengthAtLeastTwo(arr) << endl;

    return 0;
}