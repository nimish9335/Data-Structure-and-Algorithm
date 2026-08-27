#include <bits/stdc++.h>
using namespace std;

void demoOrderedSet() {
    set<int> s;
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(10);

    cout << "Ordered set: ";
    for (int x : s) cout << x << " ";
    cout << endl;

    if (s.find(20) != s.end()) cout << "20 found in set" << endl;

    auto it = s.lower_bound(15);
    cout << "lower_bound(15): " << *it << endl;

    s.erase(10);
    cout << "After erase(10): ";
    for (int x : s) cout << x << " ";
    cout << endl;
}

void demoUnorderedSet() {
    unordered_set<int> us;
    us.insert(30);
    us.insert(10);
    us.insert(20);
    us.insert(10);

    cout << "Unordered set: ";
    for (int x : us) cout << x << " ";
    cout << endl;

    if (us.count(20)) cout << "20 exists in unordered_set" << endl;

    us.erase(10);
    cout << "After erase(10): ";
    for (int x : us) cout << x << " ";
    cout << endl;
}

void demoMultiset() {
    multiset<int> ms;
    ms.insert(10);
    ms.insert(10);
    ms.insert(20);

    cout << "Multiset: ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    ms.erase(ms.find(10));
    cout << "After removing one 10: ";
    for (int x : ms) cout << x << " ";
    cout << endl;
}

void demoUnorderedMultiset() {
    unordered_multiset<int> ums;
    ums.insert(5);
    ums.insert(5);
    ums.insert(7);

    cout << "Unordered multiset: ";
    for (int x : ums) cout << x << " ";
    cout << endl;

    cout << "Count of 5: " << ums.count(5) << endl;
}

int main() {
    demoOrderedSet();
    cout << endl;

    demoUnorderedSet();
    cout << endl;

    demoMultiset();
    cout << endl;

    demoUnorderedMultiset();

    return 0;
}
