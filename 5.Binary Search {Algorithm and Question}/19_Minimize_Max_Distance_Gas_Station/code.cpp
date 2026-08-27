#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
double minimiseMaxDistanceBrute(vector<int>& stations, int k) {
    int n = stations.size();
    vector<double> gaps(n - 1);
    vector<int> parts(n - 1, 1);

    for (int i = 0; i < n - 1; i++) {
        gaps[i] = stations[i + 1] - stations[i];
    }

    for (int placed = 0; placed < k; placed++) {
        int worstIdx = 0;
        double worstLen = gaps[0] / parts[0];

        for (int i = 1; i < n - 1; i++) {
            double len = gaps[i] / parts[i];
            if (len > worstLen) {
                worstLen = len;
                worstIdx = i;
            }
        }

        parts[worstIdx]++;
    }

    double ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, gaps[i] / parts[i]);
    }

    return ans;
}

// ---------- Approach 2: Priority Queue / Max-Heap ----------
double minimiseMaxDistanceHeap(vector<int>& stations, int k) {
    int n = stations.size();
    vector<double> gaps(n - 1);
    vector<int> parts(n - 1, 1);

    // max-heap of (current piece length, gap index)
    priority_queue<pair<double, int>> pq;

    for (int i = 0; i < n - 1; i++) {
        gaps[i] = stations[i + 1] - stations[i];
        pq.push({gaps[i] / parts[i], i});
    }

    for (int placed = 0; placed < k; placed++) {
        auto it = pq.top();
        int len=it.first;
        int idx=it.second;
        pq.pop();

        parts[idx]++;
        pq.push({gaps[idx] / parts[idx], idx});
    }

    return pq.top().first;
}

// ---------- Approach 3: Binary Search on Answer (Optimal) ----------

// Total new stations needed if every piece must be <= dist.
long long stationsNeeded(vector<double>& gaps, double dist) {
    long long cnt = 0;

    for (double g : gaps) {
        long long pieces = (long long)(g / dist);
        if ((double)pieces * dist == g) {
            pieces--; // exact multiple: one fewer new station needed
        }
        cnt += pieces;
    }

    return cnt;
}

double minimiseMaxDistanceBinarySearch(vector<int>& stations, int k) {
    int n = stations.size();
    vector<double> gaps(n - 1);

    for (int i = 0; i < n - 1; i++) {
        gaps[i] = stations[i + 1] - stations[i];
    }

    double low = 0.0;
    double high = *max_element(gaps.begin(), gaps.end());
    double precision = 1e-6;

    while (high - low > precision) {
        double mid = (low + high) / 2.0;

        if (stationsNeeded(gaps, mid) <= k) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return high;
}

int main() {
    cout << fixed << setprecision(5);

    vector<int> stations1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k1 = 9;
    cout << "Brute Force:    " << minimiseMaxDistanceBrute(stations1, k1) << endl;
    cout << "Priority Queue: " << minimiseMaxDistanceHeap(stations1, k1) << endl;
    cout << "Binary Search:  " << minimiseMaxDistanceBinarySearch(stations1, k1) << endl;

    vector<int> stations2 = {1, 13, 17, 23};
    int k2 = 5;
    cout << "\nBrute Force:    " << minimiseMaxDistanceBrute(stations2, k2) << endl;
    cout << "Priority Queue: " << minimiseMaxDistanceHeap(stations2, k2) << endl;
    cout << "Binary Search:  " << minimiseMaxDistanceBinarySearch(stations2, k2) << endl;

    return 0;
}
