#include <bits/stdc++.h>
using namespace std;

/*-------------------------------------------------------
    1. Sort in Ascending Order
-------------------------------------------------------*/

bool ascending(int a, int b) {
    return a < b;
}

/*-------------------------------------------------------
    2. Sort in Descending Order
-------------------------------------------------------*/

bool descending(int a, int b) {
    return a > b;
}

/*-------------------------------------------------------
    3. Sort Pair
       First Ascending
       Second Descending
-------------------------------------------------------*/

bool pairComparator(pair<int,int> a, pair<int,int> b) {

    if(a.first == b.first)
        return a.second > b.second;

    return a.first < b.first;
}

/*-------------------------------------------------------
    4. Sort String According to Length
-------------------------------------------------------*/

bool lengthComparator(string a, string b) {

    return a.length() < b.length();
}

/*-------------------------------------------------------
    5. Sort Vector According to Sum
-------------------------------------------------------*/

bool vectorComparator(vector<int> a, vector<int> b){

    int sum1 = accumulate(a.begin(), a.end(), 0);
    int sum2 = accumulate(b.begin(), b.end(), 0);

    return sum1 < sum2;
}

int main(){

    //=========================================
    // Integer Sorting
    //=========================================

    vector<int> nums = {8,3,6,1,9,2};

    sort(nums.begin(), nums.end(), ascending);

    cout<<"Ascending\n";

    for(auto x : nums)
        cout<<x<<" ";

    cout<<"\n\n";

    sort(nums.begin(), nums.end(), descending);

    cout<<"Descending\n";

    for(auto x : nums)
        cout<<x<<" ";

    cout<<"\n\n";

    //=========================================
    // Pair Sorting
    //=========================================

    vector<pair<int,int>> vp = {

        {2,4},
        {1,9},
        {2,8},
        {3,1},
        {1,5}

    };

    sort(vp.begin(), vp.end(), pairComparator);

    cout<<"Pair Sorting\n";

    for(auto x : vp)
        cout<<"("<<x.first<<","<<x.second<<") ";

    cout<<"\n\n";

    //=========================================
    // String Sorting
    //=========================================

    vector<string> names = {

        "Rahul",
        "A",
        "Programming",
        "Code",
        "Nimish"

    };

    sort(names.begin(), names.end(), lengthComparator);

    cout<<"String Length Sorting\n";

    for(auto x : names)
        cout<<x<<" ";

    cout<<"\n\n";

    //=========================================
    // Vector Sorting
    //=========================================

    vector<vector<int>> matrix = {

        {1,2},
        {5,5},
        {4},
        {2,2,2},
        {10}

    };

    sort(matrix.begin(), matrix.end(), vectorComparator);

    cout<<"Vector Sum Sorting\n";

    for(auto row : matrix){

        cout<<"{ ";

        for(auto x : row)
            cout<<x<<" ";

        cout<<"}\n";
    }

}