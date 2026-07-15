#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long a = llabs((long long)dividend);
        long long b = llabs((long long)divisor);

        long long quotient = 0;

        while (a >= b) {
            int shift = 0;
            while (a >= (b << (shift + 1)))
                shift++;

            quotient += (1LL << shift);
            a -= (b << shift);
        }

        if ((dividend < 0) ^ (divisor < 0))
            quotient = -quotient;

        return (int)quotient;
    }
};