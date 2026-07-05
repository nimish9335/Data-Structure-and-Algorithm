/*
==========================================
Bit Tricks and Techniques
==========================================

Topics
1. Swap Two Numbers
2. Check i-th Bit
3. Set i-th Bit
4. Clear i-th Bit
5. Toggle i-th Bit
6. Remove Last Set Bit
7. Check Power of Two
8. Count Set Bits
*/

#include<bits/stdc++.h>
using namespace std;

// Swap using XOR
void swapXOR(int &a,int &b){
    if(a==b) return;

    a=a^b;
    b=a^b;
    a=a^b;
}

// Check i-th bit
bool checkBit(int n,int i){
    return (n&(1<<i));
}

// Set i-th bit
int setBit(int n,int i){
    return n|(1<<i);
}

// Clear i-th bit
int clearBit(int n,int i){
    return n&(~(1<<i));
}

// Toggle i-th bit
int toggleBit(int n,int i){
    return n^(1<<i);
}

// Remove last set bit
int removeLastSetBit(int n){
    return n&(n-1);
}

// Check power of two
bool isPowerOfTwo(int n){
    return n>0 && (n&(n-1))==0;
}

// Count set bits (Naive)
int countSetBitsNaive(int n){
    int count=0;

    while(n){
        count+=n&1;
        n>>=1;
    }

    return count;
}

// Count set bits (Optimized)
int countSetBits(int n){
    int count=0;

    while(n){
        count++;
        n=n&(n-1);
    }

    return count;
}