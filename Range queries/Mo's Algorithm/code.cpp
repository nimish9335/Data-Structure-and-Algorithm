#include <bits/stdc++.h>
using namespace std;

int blockSize;
vector<int> arr, freq;
long long curAns = 0;

struct Query {
    int l, r, idx;
};

void add(int x) {
    freq[arr[x]]++;
    if (freq[arr[x]] == 1) curAns++;
}

void remove(int x) {
    freq[arr[x]]--;
    if (freq[arr[x]] == 0) curAns--;
}

bool cmp(Query a, Query b) {
    int blockA = a.l / blockSize;
    int blockB = b.l / blockSize;
    if (blockA != blockB) return blockA < blockB;
    if (blockA % 2 == 0) return a.r < b.r;
    return a.r > b.r;
}

int main() {
    int n;
    cin >> n;
    arr.resize(n);
    for (auto& x : arr) cin >> x;

    int maxVal = *max_element(arr.begin(), arr.end());
    freq.assign(maxVal + 1, 0);
    blockSize = max(1, (int)sqrt(n));

    int q;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(), cmp);

    vector<long long> answer(q);
    int curL = 0, curR = -1;

    for (auto& query : queries) {
        int l = query.l, r = query.r;
        while (curR < r) { curR++; add(curR); }
        while (curL > l) { curL--; add(curL); }
        while (curR > r) { remove(curR); curR--; }
        while (curL < l) { remove(curL); curL++; }
        answer[query.idx] = curAns;
    }

    for (int i = 0; i < q; i++) cout << answer[i] << "\n";
    return 0;
}
