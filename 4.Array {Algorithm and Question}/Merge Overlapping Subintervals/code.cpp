#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeIntervalsBrute(vector<vector<int>>& intervals) {
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    vector<bool> merged(n, false);

    for (int i = 0; i < n; i++) {
        if (merged[i]) continue;

        int start = intervals[i][0];
        int end = intervals[i][1];

        for (int j = i + 1; j < n; j++) {
            if (intervals[j][0] <= end) {
                end = max(end, intervals[j][1]);
                merged[j] = true;
            }
        }

        result.push_back({start, end});
    }

    return result;
}

vector<vector<int>> mergeIntervalsOptimal(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    result.push_back(intervals[0]);

    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i][0] <= result.back()[1]) {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {
            result.push_back(intervals[i]);
        }
    }

    return result;
}

void printIntervals(vector<vector<int>>& intervals) {
    for (auto& iv : intervals) {
        cout << "[" << iv[0] << "," << iv[1] << "] ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> arr1 = {{1,3}, {2,6}, {8,10}, {15,18}};
    vector<vector<int>> res1 = mergeIntervalsOptimal(arr1);
    cout << "Optimal Result: ";
    printIntervals(res1);

    vector<vector<int>> arr2 = {{1,4}, {4,5}};
    vector<vector<int>> res2 = mergeIntervalsBrute(arr2);
    cout << "Brute Force Result: ";
    printIntervals(res2);

    return 0;
}
