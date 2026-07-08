#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minBitFlips(int start, int goal) {
        int x = start ^ goal;
        int cnt = 0;

        while (x) {
            cnt += (x % 2);
            x /= 2;
        }

        return cnt;
    }
};