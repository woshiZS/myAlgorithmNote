#include <iostream>
#include <vector>
using namespace std;

int lower_bound(vector<int>& a, int target){
    int l = 0, r = a.size();
    while(l < r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int upper_bound(vector<int>& a, int target){
    int l = 0, r = a.size();
    while(l < r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] > target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int binary_search(vector<int>& a, int target){
    int l = 0, r = a.size() - 1;
    while(l <= r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] == target)
            return mid;
        else if(a[mid] > target)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int main(int argc, char **argv){
    vector<int> arr = {1, 2, 2, 3, 4, 4, 4, 4, 5, 6, 7, 9, 9, 10};
    cout << "The original arr is: \n";
    for(auto& num : arr)
        cout << num << " ";
    cout << endl;
    cout << "The lower bound of 4 in arr is " << lower_bound(arr, 4) << endl;
    cout << "The higher bound of 4 in arr is " << upper_bound(arr, 4) << endl;
    cout << "The lower bound of 11 in arr is " << lower_bound(arr, 11) << endl;
    return 0;
}